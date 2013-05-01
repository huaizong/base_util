import telnetlib
from datetime import *
import time
import hashlib
import sys
import random
import json
from multiprocessing import Process
import sys

def try_max_conn():
    tn_lst = []
    for i in range(512000):
        tn = telnetlib.Telnet('ali', 8080)
        tn_lst.append(tn)
        if len(tn_lst) % 1000 == 0:
            print len(tn_lst)
    time.sleep(3600)
    for tn in tn_lst:
        tn.close()
sample = []
for i in range(100):
    p = Process(target = try_max_conn, args=())
    p.start()
    sample.append(p)
for p in sample:
    p.join()
