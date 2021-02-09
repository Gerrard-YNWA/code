these code compares performance under `resty`(luajit)

```
resty concat_str_bench.lua
2021/02/09 10:26:33 [error] 76378#16872940: *2 [lua] concat_str_bench.lua:25: benchmark_1(): 3.000020980835, context: ngx.timer
2021/02/09 10:26:33 [error] 76378#16872940: *2 [lua] concat_str_bench.lua:36: benchmark_2(): 128.00002098083, context: ngx.timer
2021/02/09 10:26:33 [error] 76378#16872940: *2 [lua] concat_str_bench.lua:46: benchmark_3(): 1.9998550415039, context: ngx.timer
```

```
resty ffi_cdata_bench.lua
=========benchmark1 cost:5473.0000495911 ms.
=========benchmark2 cost:569.9999332428 ms.
=========benchmark3 cost:482.00011253357 ms.
```

```
resty utf8_validate_bench.lua
benchmark for plain ascii, string Hello word
- validate took 482.000113ms
- validate2 took 24.999857ms
benchmark for utf8 stuff, string ¢€𤭢
- validate took 1253.000021ms
- validate2 took 48.000097ms
benchmark for mixed stuff, string Pay in €. Thanks.
- validate took 1194.000006ms
- validate2 took 39.000034ms
```
