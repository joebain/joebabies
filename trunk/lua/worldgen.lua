young_world = {}
box_chance = 0.1
rock_chance = 0.2

function world_gen(sizex, sizey, difficulty)

  math.randomseed( os.time() )

  iterations = 0
  
  fill_world(sizex,sizey,"0")
  x = math.random(1,sizex)
  y = math.random(1,sizey)
  place(x,y,"i")
  running = true
  dir = math.random(1,4)
  for i=1,sizex do
      for j=1,sizey do
        io.write(young_world[i][j].symbol, " ")
      end
      io.write("\n")
    end
  while running do
    iterations = iterations + 1
    if (iterations > 100) then
      print("ITERATIONS EXCEEDED")
      return nil
    end
    print("difficulty is " .. difficulty)
    t = math.random(0,1)
    if (t == 0) then dir = dir + 1 else dir = dir - 1 end
    if (dir == 0) then dir = 2 end
    if (dir == 5) then dir = 3 end
    distance = 0
    stillok = true    
    if (dir == 1) then -- north
      if (y + 1 > sizey) then stillok = false end
      if stillok then
        distance = sizey
        while (y + distance > sizey) do 
          distance = math.random(1,sizey) 
        end
        if obstruction_is_on_path(dir, x, y, distance) then 
          stillok = false 
        end
        if stillok then
          if (y ~= 1 and readplace(x,y-1) == "0") then place(x,y-1,"r") end
          y = y + distance
        end
      end
    elseif (dir == 2) then -- east
      if (x + 1 > sizex) then stillok = false end
      if stillok then
        distance = sizex
        while (x + distance > sizex) do 
          distance = math.random(1,sizex) 
        end
        if obstruction_is_on_path(dir, x, y, distance) then 
          stillok = false 
        end
        if stillok then
          if (x ~= 1 and readplace(x-1,y) == "0") then place(x-1,y,"r") end
          x = x + distance
        end
      end
    elseif (dir == 3) then -- south
      if (y - 1 < 1) then stillok = false end
      if stillok then
        distance = sizey
        while (y - distance < 1) do 
          distance = math.random(1,sizey) 
        end
        if obstruction_is_on_path(dir, x, y, distance) then 
          stillok = false 
        end
        if stillok then
          if (y ~= sizey and readplace(x,y+1) == "0") then place(x,y+1,"r") end
          y = y - distance
        end
      end
    elseif (dir == 4) then -- west
      if (x - 1 < 1) then stillok = false end
      if stillok then
        distance = sizex
        while (x - distance < 1) do 
          distance = math.random(1,sizex) 
        end
        if obstruction_is_on_path(dir, x, y, distance) then 
          stillok = false 
        end
        if stillok then
          if (x ~= sizex and readplace(x+1,y) == "0") then place(x+1,y,"r") end
          x = x - distance
        end
      end
    end
    if (stillok) then
      mark_path(dir, x, y, distance)
      difficulty = difficulty - 1
      if (difficulty == 0) then running = false end
      previous_dir = dir
      if (initial) then initial = false end
    end
    for i=1,sizex do
      for j=1,sizey do
        io.write(young_world[i][j].symbol, " ")
      end
      io.write("\n")
    end
  end
  place(x,y,"g")
  attempt_to_make_things_interesting(sizex,sizey)
  return young_world
end


function fill_world(sizex, sizey, char) 
  for i=1,sizex do
    young_world[i] = {}
    for j=1,sizey do
      young_world[i][j] = {}
      young_world[i][j].symbol = char
      young_world[i][j].thing = "empty"
    end
  end
end

function obstruction_is_on_path(dir, x, y, distance)
  ok = true
  if (dir == 1) then
    for q=y,y+distance do
      if (readplace(x,q) ~= "0") then 
        ok = false
        break
      end
    end  
  elseif (dir == 2) then
    for q=x,x+distance do
      if (readplace(q,y) ~= "0") then 
        ok = false
        break
      end
    end  
  elseif (dir == 3) then
    for q=y-distance,y do
      if (readplace(x,q) ~= "0") then 
        ok = false
        break
      end
    end
  elseif (dir == 3) then
    for q=x-distance,x do
      if (readplace(q,y) ~= "0") then 
        ok = false
        break
      end
    end
  end
  return ok
end

function place(x, y, char)
  young_world[x][y].symbol = char
end

function readplace(x, y)
  return young_world[x][y].symbol
end

function mark_path(dir, x, y, distance)
  --print("woo mark path")
  --print("dir: " .. dir .. " x: " .. x .. " y: " .. y .. " dist: " .. distance)
  if (dir == 1) then
    for q=y-(distance-1),y do
      place(x,q,"!")
    end  
  elseif (dir == 2) then
    for q=x-(distance-1),x do
      place(q,y,"!")
    end  
  elseif (dir == 3) then
    for q=y,y+(distance-1) do
      place(x,q,"!")
    end
  elseif (dir == 3) then
    for q=x,x+(distance-1) do
      place(q,y,"!")
    end
  end
end


function attempt_to_make_things_interesting(sizex, sizey)
  for i=1,sizex do

    for j=1,sizey do

      if (readplace(i,j) == "0") then

        if (math.random() < rock_chance) then 
          place(i,j,"r")
        else 
          if (math.random() < box_chance) then
            place(i,j,"b")
          end
        end

      elseif (readplace(i,j) == "!") then

        if (math.random() < box_chance) then
          place(i,j,"b")
        else
          place(i,j,"0")
        end

      end

    end -- for j

  end -- for i
end
