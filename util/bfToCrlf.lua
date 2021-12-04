if #arg < 1 then
  print("lua bgToCrlf.lua [input file name]")

  return
end

local input_file, err = io.open(arg[1], "rb")
if input_file == nil then
  print(argv[1] .. " cannot be opened: " .. err)

  return
end

local output_file, err = io.open(arg[1] .. ".crlf", "wb")
if output_file == nil then
  print(argv[1] .. ".crlf cannot be opened: " .. err)

  return
end

local char_conversion_table = {
  [">"] = "\r\r\r",
  ["<"] = "\r\r\n",
  ["+"] = "\r\n\r",
  ["-"] = "\r\n\n",
  ["."] = "\n\r\r",
  [","] = "\n\r\n",
  ["["] = "\n\n\r",
  ["]"] = "\n\n\n"
}

while true do
  local ch = input_file:read(1)
  local str = char_conversion_table[ch]

  if ch == nil then
    break
  end

  if str then
    output_file:write(str)
  end
end

input_file:close()
output_file:close()