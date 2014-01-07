import sqlite3
import time

def init_db():
    sql = """create table if not exists test(
            mid integer primary key,
            name text,
            ctime int
            );
        """
    db = sqlite3.Connection("./test.db")
    cur = db.cursor()
    cur.execute(sql)
    db.close()

def add_rec():
    sql = """insert into test(name, ctime)values(?, ?);"""
    db = sqlite3.Connection("./test.db")
    cur = db.cursor()
    name_txt = """???name

value"""
    cur.execute(sql, [name_txt, int(time.time())])
    db.commit()
    sql = "select * from test"
    cur.execute(sql)
    des = cur.fetchall()
    for row in des:
        print row
    db.close()
init_db()
add_rec()
