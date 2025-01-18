-- main.lua
local function getShimloaderPaths()
    -- Get the current script's directory
    local src = debug.getinfo(1).source
    local baseDir = src:sub(2, src:find("\\Mods\\Moddy-VotVDiscordRPC", 1, true) - 1)
    
    -- Read shimloader log
    local shimLog = io.open(baseDir.."\\shimloader-log.txt", "rb"):read("*all")
    
    -- Helper function to extract paths
    local function extractPath(flag)
        local start = shimLog:find(flag, 1, true) + 12
        start = shimLog:find("\"", start, true) + 1
        local finish = shimLog:find("\"", start, true) - 1
        return (shimLog:sub(start, finish):gsub("\\\\", "\\"))
    end
    
    -- Extract all paths
    local pathCfg = extractPath("--cfg-dir")
    local pathMod = extractPath("--mod-dir")
    local pathPak = extractPath("--pak-dir")
    
    return baseDir, pathCfg, pathMod, pathPak
end

-- Get all necessary paths
local baseDir, pathCfg, pathMod, pathPak = getShimloaderPaths()

-- Get the mod directory path
local modDir = debug.getinfo(1).source:match("@(.*)\\scripts\\main.lua")

-- Call Python script with the necessary paths
local pythonScriptPath = pathMod.."\\Moddy-VotVDiscordRPC\\scripts\\mod_handler.exe"
local cmd = string.format('%s "%s" "%s" "%s" "%s" "%s"', 
    pythonScriptPath, modDir, pathMod, baseDir, pathCfg, pathPak)


print(cmd)
os.execute(cmd)