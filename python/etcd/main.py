#!/bin/python

import etcd3

etcd = etcd3.client()

print( etcd.get("/dir/v3/d"))
print( etcd.delete("/dir/v3/not_exist"))
