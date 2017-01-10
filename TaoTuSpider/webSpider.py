#!/usr/bin/env python
# coding=utf-8

import os
import sys
import urllib
import threading
import Queue
import random
from bs4 import BeautifulSoup

reload(sys)
sys.setdefaultencoding('utf-8')

baseUrl = "http://www.aitaotu.com"

def getHtml(url):
    htmlPage = urllib.urlopen(url)
    htmlText = htmlPage.read()
    return htmlText

class PagePicsDownloadThread(threading.Thread):

	def __init__(self, queue, index):
		threading.Thread.__init__(self)
		self.urlQueue = queue
		self.index = index

	def run(self):
		while True:
			try:
				url = self.urlQueue.get(block = False)
				identifier = random.randint(10000, 100000)
				basePath = './Pics/AiTaoTu/PicSet%s/' % identifier
				os.mkdir(basePath)

				count = 1
				nextPage = self.downloadSinglePagePics(url, basePath, count)
				while nextPage:
					pageUrl = baseUrl + nextPage['href']
					nextPage = self.downloadSinglePagePics(pageUrl, basePath, count)
			except Queue.Empty:
				break

	def downloadSinglePagePics(self, url, basePath, count):
		downHtml = getHtml(url)
		soup = BeautifulSoup(downHtml)
		title = soup.find('title')
		print "线程%s的当前位置：" % self.index, title.string

		picDiv = soup.find('div', id = 'big-pic')
		items = picDiv.find_all('img')
		for item in items:
			name = item['alt']
			imgUrl = item['src']
			filename = os.path.basename(imgUrl)
			path = basePath + filename
			print "线程%s正在下载第%s张图片......" % (self.index, count)
			urllib.urlretrieve(imgUrl, path)
			count = count + 1

		pages = soup.find('div', class_ = 'pages')
		nextPage = pages.find('a', text = '下一页')

		return nextPage

def downTagPictures(itemDict):
	threadSize = 10
	threadSet = []
	q = Queue.Queue()

	print "正在添加所有需要处理的URL至工作队列......"
	for item in itemDict.values():
		url = baseUrl + item
		q.put(url)

	print "线程启动，开始下载图片......"
	for i in range(threadSize):
		thread = PagePicsDownloadThread(q, i)
		thread.start()
		threadSet.append(thread)

	for thread in threadSet:
		thread.join()

def obtainPageItems(soup, itemDict):
	parentDiv = soup.find('div', id = 'mainbody')
	pageItems = parentDiv.find_all('a', class_ = 'Pli-litpic')

	for item in pageItems:
		title = item['title']
		href = item['href']
		itemDict[title] = href

def parseTagHtml(url):
	itemDict = {}
	tagHtml = getHtml(url)
	soup = BeautifulSoup(tagHtml)
	obtainPageItems(soup, itemDict)

	nextPage = soup.find('a', text = '下一页')
	while nextPage:
		extUrl = nextPage['href']
		url = baseUrl + extUrl
		tagHtml = getHtml(url)
		soup = BeautifulSoup(tagHtml)
		obtainPageItems(soup, itemDict)
		nextPage = soup.find('a', text = '下一页')

	return itemDict

# 该函数主要用于分析最初的按标签查找的页面
def parseMainHtml(html):
	soup = BeautifulSoup(html)
	mainElements = soup.select('body > div.Clbc_top > div.tagtypelist')
	tagTypeList = mainElements[0].find_all('div', class_='tags_list')

	tagUrlDict = {}
	tagList = []
	for tagType in tagTypeList :
		dlElement = tagType.find('dl')
		dlName = dlElement.find('dt').string
		tagUrlList = dlElement.find('dd').find_all('a')
		for tagUrl in tagUrlList :
			tagName = tagUrl.string
			urlString = tagUrl['href']
			tagUrlDict[tagName] = urlString
			tagList.append(tagName)

	return tagUrlDict, tagList

def mainThread():
	mainUrl = baseUrl + "/tag"
	mainHtml = getHtml(mainUrl)
	tagdict, taglist = parseMainHtml(mainHtml)
	index = 0
	for tag in taglist:
		print "%s." % index, tag
		index = index + 1

	num = input("\n请选择一个感兴趣的标签进行下载: ")
	tagUrl = baseUrl + tagdict[taglist[num]]
	print "\n指定标签对应的URL地址为: ", tagUrl
	urlDict = parseTagHtml(tagUrl)
	print "\n对应标签的所有子项目如下所示: "
	index = 0
	for (key, value) in urlDict.items():
		print "%s." % index, key, ":", baseUrl + value
		index = index +1
	print "\n现在开始下载对应标签下的所有图片......"
	print "下载说明：爬虫通过若干个并发线程进行同时下载，各个子项的所有图片保存在不同的随机命名的文件夹中。"
	downTagPictures(urlDict)

if __name__ == '__main__':
	mainThread()
