---------------------------------------------------------------------------
--
--     Filename:  ffi_cdata_bench.lua
--
--  Description:  benchmark for optimization for masked payload in
--                https://github.com/openresty/lua-resty-websocket
--
--      Version:  1.0
--      Created:  02/09/2021 10:36:11
--     Revision:  None
--
--       Author:  gerrard (gerrard), <gyc.ssdut@gmail.com>
--      Company:  
--
---------------------------------------------------------------------------
local bit = require("bit")
local ffi = require("ffi")
local str_char = string.char
local concat = table.concat
local byte = string.byte
local bxor = bit.bxor
local ffi_new = ffi.new
local ffi_string = ffi.string

local ok, new_tab = pcall(require, "table.new")
if not ok then
    new_tab = function () return {} end
end


local masking_key = 0x0f3eca1d
local payload_len = 3200
local f = io.open("./111.wav", "rb")
local payload = f:read(payload_len)
f:close()

local count  = 100000

local str_buf_size = 4096
local str_buf
local c_buf_type = ffi.typeof("char[?]")

local function get_string_buf(size, must_alloc)
    if size > str_buf_size or must_alloc then
        return ffi_new(c_buf_type, size)
    end
    if not str_buf then
        str_buf = ffi_new(c_buf_type, str_buf_size)
    end

    return str_buf
end


local function implement1()
    local bytes = new_tab(payload_len, 0)
    for i = 1, payload_len do
        bytes[i] = str_char(bxor(byte(payload, i),
                                byte(masking_key, (i - 1) % 4 + 1)))
    end
    local p = concat(bytes)
    return p
end


local function implement2()
    local buffer = ffi_new("char[?]", payload_len)
    for i = 1, payload_len do
        buffer[i-1] = bxor(byte(payload, i),
                                byte(masking_key, (i - 1) % 4 + 1))
    end
    local p = ffi_string(buffer, payload_len)
    return p
end

local function implement3()
    local buffer = get_string_buf(payload_len)
    for i = 1, payload_len do
        buffer[i-1] = bxor(byte(payload, i),
                                byte(masking_key, (i - 1) % 4 + 1))
    end
    local p = ffi_string(buffer, payload_len)
    return p
end

local function benchmark1()
    ngx.update_time()
    local start_time = ngx.now()
    for i = 1, count do
        implement1()
    end
    ngx.update_time()
    ngx.say("=========benchmark1 cost:", (ngx.now()-start_time) * 1000, " ms.")
end

local function benchmark2()
    ngx.update_time()
    local start_time = ngx.now()
    for i = 1, count do
        implement2()
    end
    ngx.update_time()
    ngx.say("=========benchmark2 cost:", (ngx.now()-start_time) * 1000, " ms.")
end

local function benchmark3()
    ngx.update_time()
    local start_time = ngx.now()
    for i = 1, count do
        implement3()
    end
    ngx.update_time()
    ngx.say("=========benchmark3 cost:", (ngx.now()-start_time) * 1000, " ms.")
end

local function compare()
    local payload1 = implement1()
    local payload2 = implement2()
    local payload3 = implement2()
    ngx.say(payload1==payload2)
    ngx.say(payload2==payload3)
end

--compare()
benchmark1()
benchmark2()
benchmark3()
