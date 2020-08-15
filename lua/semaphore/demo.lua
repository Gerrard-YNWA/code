---------------------------------------------------------------------------
--
--     Filename:  demo.lua
--
--  Description:  semaphore demo 
--
--      Version:  1.0
--      Created:  08/14/2020 18:06:46
--     Revision:  None
--
--       Author:  gerrard (gerrard), <gyc.ssdut@gmail.com>
--      Company:  
--
---------------------------------------------------------------------------
local semaphore = require("ngx.semaphore")
local format = string.format

local sema, err = semaphore:new()

local function consume(premature, id)
    local start = ngx.now()
    while ngx.now() - start < 3 do
        local ok, err = sema:wait(1)
        ngx.log(ngx.ERR, format("###consumer %s: %s, %s", id, ok, err))
    end
end

local function produce(premature)
    sema:post(5)
end

for i = 1, 5 do
    ngx.timer.at(0, consume, i)
    ngx.sleep(0.1)
end

ngx.timer.at(0, produce)
