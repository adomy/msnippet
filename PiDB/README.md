piDB
--------

piDB is lightweight, fast, and simple database based on the `simplejson <https://pypi.python.org/pypi/simplejson/>`_ module.


piDB is Fun
```````````````

    >>> import pidb

    >>> db = pidb.load('test.db', False)

    >>> db.set('key', 'value')

    >>> db.get('key')
    'value'

    >>> db.dump()
    True
