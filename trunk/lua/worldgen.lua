young_world = {}
-- The bits you tweak
box_chance = 0.1
rock_chance = 0.05
allowed_iterations = 100

function world_gen(sizex, sizey, difficulty)



  iterations = 0
  
  fill_world(sizex,sizey,"0")
  x = math.random(2,sizex-1)
  y = math.random(2,sizey-1)
  place(x,y,"i")
  running = true
  dir = math.random(1,4)
  prev_dir = dir
  --print("Initial puzzle:")
  --print_world_state(sizex,sizey)
  while running do
    iterations = iterations + 1
    if (iterations > allowed_iterations) then
      print("ITERATIONS EXCEEDED")
      return nil
    end
    --print("difficulty is now " .. difficulty)

    --print("dir was: "..dir)
    t = math.random(1,2)
    if (t == 1) then dir = dir + 1 else dir = dir - 1 end
    if (dir == 0) then dir = 4 end
    if (dir == 5) then dir = 1 end
    --print("attempting dir: "..dir)

    distance = 0
    stillok = true    

    if (dir == 1) then -- north
      if (y == sizey) then 
        --print("At edge, can't go north")
        stillok = false 
      end
      if stillok then
        distance = sizey
        while (y + distance > sizey) do 
          distance = math.random(1,sizey-1) 
        end
        --print("possible distance is "..distance)
        if obstruction_is_on_path(dir, x, y, distance) then 
          --print("path is somehow obstructed")
          stillok = false 
        end
        if stillok then
          if (y ~= 1 and readplace(x,y-1) == "0") then place(x,y-1,"r") end
          y = y + distance
        end
      end
    elseif (dir == 2) then -- east
      if (x == sizex) then 
        --print("At edge, can't go east")
        stillok = false 
      end
      if stillok then
        distance = sizex
        while (x + distance > sizex) do 
          distance = math.random(1,sizex-1) 
        end
        --print("possible distance is "..distance)
        if obstruction_is_on_path(dir, x, y, distance) then 
          --print("path is somehow obstructed")
          stillok = false 
        end
        if stillok then
          if (x ~= 1 and readplace(x-1,y) == "0") then place(x-1,y,"r") end
          x = x + distance
        end
      end
    elseif (dir == 3) then -- south
      if (y == 1) then 
        --print("At edge, can't go south")
        stillok = false 
      end
      if stillok then
        distance = sizey
        while (y - distance < 1) do 
          distance = math.random(1,sizey-1) 
        end
        --print("possible distance is "..distance)
        if obstruction_is_on_path(dir, x, y, distance) then 
          --print("path is somehow obstructed")
          stillok = false 
        end
        if stillok then
          if (y ~= sizey and readplace(x,y+1) == "0") then place(x,y+1,"r") end
          y = y - distance
        end
      end
    elseif (dir == 4) then -- west
      if (x == 1) then 
        --print("At edge, can't go west")
        stillok = false 
      end
      if stillok then
        distance = sizex
        while (x - distance < 1) do 
          distance = math.random(1,sizex-1) 
        end
        --print("possible distance is "..distance)
        if obstruction_is_on_path(dir, x, y, distance) then 
          --print("path is somehow obstructed")
          stillok = false 
        end
        if stillok then
          if (x ~= sizex and readplace(x+1,y) == "0") then place(x+1,y,"r") end
          x = x - distance
        end
      end
    end -- end of direction choice
    if (stillok) then
      mark_path(dir, x, y, distance)
      --print("moving " .. distance .. " units")
      difficulty = difficulty - 1
      if (difficulty == 0) then running = false end
      prev_dir = dir
      if (initial) then initial = false end
      --print("Successful step added.")
      --print("Current world:")
      --print_world_state(sizex,sizey)
    else
      dir = prev_dir
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
  --print("actually checking for obstructions")
  ob = false
  if (dir == 1) then
    for q=y+1,y+distance do
      if (readplace(x,q) == "r" or readplace(x,q) == "i") then 
        ob = true
      end
    end  
  elseif (dir == 2) then
    for q=x+1,x+distance do
      if (readplace(q,y) == "r"  or readplace(q,y) == "i") then 
        ob = true
      end
    end  
  elseif (dir == 3) then
    for q=y-distance,y-1 do
      if (readplace(x,q) == "r"  or readplace(x,q) == "i") then 
        ob = true
      end
    end
  elseif (dir == 3) then
    for q=x-distance,x-1 do
      if (readplace(q,y) == "r"  or readplace(q,y) == "i") then 
        ob = true
      end
    end
  end
  return ob
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
  elseif (dir == 4) then
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

function print_world_state(sizex, sizey) 
  for a=1,sizex do
    for b=1,sizey do
      io.write(young_world[a][b].symbol, " ")
    end
    io.write("\n")
  end
end

