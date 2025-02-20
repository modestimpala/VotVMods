local function getShimloaderPaths()
    -- Get the current script's directory
    local src = debug.getinfo(1).source
    local baseDir = src:sub(2, src:find("\\Mods\\Moddy-SmartTV", 1, true) - 1)
    
    -- Read shimloader log
    local shimLog = io.open(baseDir.."\\shimloader-log.txt", "rb"):read("*all")
    
    -- Extract pak path
    local start = shimLog:find("--pak-dir", 1, true) + 12
    start = shimLog:find("\"", start, true) + 1
    local finish = shimLog:find("\"", start, true) - 1
    local pakPath = shimLog:sub(start, finish):gsub("\\\\", "\\")
    
    -- Write pak path to file
    local outFile = io.open(baseDir.."\\pakdir.txt", "w")
    outFile:write(pakPath)
    outFile:close()
end

getShimloaderPaths()