---------------------------------------------------------------------------
--
--     Filename:  concat_str_bench.lua
--
--  Description:  benchmark for concat with very few str
--
--      Version:  1.0
--      Created:  02/09/2021 10:25:12
--     Revision:  None
--
--       Author:  gerrard (gerrard), <gyc.ssdut@gmail.com>
--      Company:  
--
---------------------------------------------------------------------------
local concat = table.concat
local format = string.format

local function benchmark_1()
    ngx.update_time()
    local start = ngx.now()
    for i=1, 10000000 do
        local a = "vad_pause_time=" .. "200"
    end
    ngx.update_time()
    ngx.log(ngx.ERR, (ngx.now() - start) * 1000)
end

local function benchmark_2()
    ngx.update_time()
    local t = {"vad_pause_time=", "200"}
    local start = ngx.now()
    for i=1, 10000000 do
        local a = concat(t)
    end
    ngx.update_time()
    ngx.log(ngx.ERR, (ngx.now() - start) * 1000)
end

local function benchmark_3()
    ngx.update_time()
    local start = ngx.now()
    for i=1, 10000000 do
        local a = format("%s=%s", "vad_pause_time", "200")
    end
    ngx.update_time()
    ngx.log(ngx.ERR, (ngx.now() - start) * 1000)
end


benchmark_1()
benchmark_2()
benchmark_3()
