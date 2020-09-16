WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

PADDLE_SPEED = 200

--[[Please figure out that push and class libraries are not included for copyright's sake
so if you want to run the game make sure you go into the respective git hubs and download the files
from their very own creators]]


-- push is a library that allow us to draw our game at a virtual resolution,
-- providing more retro aesthetic
--
-- https://github.com/Ulydev/push
Class = require 'class'
push = require 'push'

require 'Ball'
require 'Paddle'

-- gamestate variable used to track wheter the ball should move or not
gamestate = 'start' 

function love.load()
    -- write the title up on the screen
    love.window.setTitle('Pong')

    -- seeds the math.random function
    math.randomseed(os.time())

    -- changes the default filter from bilinear to nearest - neighbor
    love.graphics.setDefaultFilter('nearest', 'nearest')

    -- Players score tracking
    player1Score = 0
    player2Score = 0

    servingPlayer =  math.random(2) == 1 and 1 or 2

    winningPlayer = 0 

    -- Better fonts for the game purpose
    smallfont = love.graphics.newFont('Font.ttf', 8)
    mediumfont = love.graphics.newFont('Font.ttf', 32)
    victoryFont = love.graphics.newFont('Font.ttf', 24)
    love.graphics.setFont(smallfont)

    -- Sounds used on each of the discribed situations 
    sounds = {
        ['paddle_hit'] = love.audio.newSource('Paddle_hit.wav', 'static'),
        ['point_scored'] = love.audio.newSource('point_scored.wav', 'static'),
        ['wall_hit'] = love.audio.newSource('Wall_hit.wav', 'static')
    }

    -- sets up a virtual window in order to zoom in
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = true
    })

    -- initialize the paddles
    paddle1 = Paddle(5, 20, 5, 20)
    paddle2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)

    -- initialize the ball
    ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    if servingPlayer == 1 then
        ball.dx = 100
    else
        ball.dx = -100
    end
end

function love.resize(w, h)
    push:resize(w,h)
end

-- Updating function (frames)
function love.update(dt)
    if gamestate == 'play' then

        -- fuction to update the player's score and reset the ball 
        if ball.x < 0 then
            player2Score = player2Score + 1
            servingPlayer = 1
            ball:reset()
            ball.dx = 100

            sounds['point_scored']:play()

            if player2Score >= 2 then
                winningPlayer = 2
                gamestate = 'victory'
            else
                gamestate = 'serve'
            end
        end
        
        if ball.x > VIRTUAL_WIDTH - 4 then
            player1Score = player1Score + 1
            servingPlayer = 2
            ball:reset()
            ball.dx = -100

            sounds['point_scored']:play()

            if player1Score >= 2 then
                winningPlayer = 1
                gamestate = 'victory'
            else
                gamestate = 'serve'
            end
        end

        -- check for collisions with paddles
        if ball:collides(paddle1) then
            -- deflect the ball to the right
            ball.dx = -ball.dx * 1.03
            ball.x = paddle1.x + 5

            -- plays the sound if there's a collision
            sounds['paddle_hit']:play()

            -- randomize the velocity of the ball
            if ball.dy < 0 then
                ball.dy = -math.random(10,150)
            else
                ball.dy = math.random(10,150)
            end
        end

        if ball:collides(paddle2) then
            -- deflect the ball to the left
            ball.dx = -ball.dx
            ball.x = paddle2.x - 5

            -- plays the sound if there's a collision
            sounds['paddle_hit']:play()

            -- randomize the velocity of the ball
            if ball.dy < 0 then
                ball.dy = -math.random(10,150)
            else
                ball.dy = math.random(10,150)
            end
        end

        if ball.y <= 0 then
            -- deflect ball down
            ball.dy = -ball.dy
            ball.y = 0

            -- trigger the wall hit sound wheter it hits the top or bottom screen
            sounds['wall_hit']:play()
        end

        if ball.y >= VIRTUAL_HEIGHT - 4 then
            -- deflect ball up
            ball.dy = -ball.dy
            ball.y = VIRTUAL_HEIGHT- 4

            -- trigger the wall hit sound wheter it hits the top or bottom screen
            sounds['wall_hit']:play()
        end


        -- functions to implement movement on paddles, relies on Paddle class
        paddle1:update(dt)
        paddle2:update(dt)

        -- Render paddle movement depending on user's input ( 1st player)
        if love.keyboard.isDown('w') then
            paddle1.dy =  - PADDLE_SPEED
        elseif love.keyboard.isDown('s') then
            paddle1.dy = PADDLE_SPEED
        else
            paddle1.dy = 0
        end
        
        -- Render paddle movement depending on user's input ( 2nd player)
        if gamestate == 'play' then
            -- AI moviments
            if ball.x > math.random(VIRTUAL_WIDTH / 2, VIRTUAL_WIDTH) then
                if ball.y + ball.height / 2 < paddle2.y  then
                    -- Moves upside with variation of velocity to make it possible to win
                    paddle2.dy = math.random(-PADDLE_SPEED, -PADDLE_SPEED / 3)    
                elseif ball.y + ball.height / 2 > paddle2.y + paddle2.height then
                    -- Moves downside with variation of velocity to make it possible to win
                    paddle2.dy = math.random(PADDLE_SPEED / 3, PADDLE_SPEED)
                else
                    -- In case the paddle is in the same position as the ball stand still
                    paddle2.dy = 0
                end
            end
        end

        -- Render ball movement if enter has been pressed before  
        if gamestate == 'play' then
            ball:update(dt)
        end
    end
end

function love.keypressed(key)

    -- quit the game if esc is pressed
    if key == 'escape' then
        love.event.quit()

    -- Makes the ball move or not relying on enter input    
    elseif key == 'enter' or key == 'return' then
        if gamestate == 'start' then
            gamestate = 'serve'
        -- works upon the victory stage
        elseif gamestate == 'victory' then

            -- resets the player's scores
            player1Score = 0
            player2Score = 0
            -- go back to the starting phase
            gamestate = 'start'

        -- checks for the serve stage
        elseif gamestate == 'serve' then
            gamestate = 'play'
        end
    end
end       

function love.draw()
    push:apply('start')

    -- change the screen collor to a sort of blue
    love.graphics.clear(40 / 255, 45 / 255, 52 / 255, 255 / 255)

    -- Render initial messages
    if gamestate == 'start' then
        love.graphics.setFont(smallfont)
        love.graphics.printf("Welcome to Pong!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Play!", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gamestate == 'serve' then
        love.graphics.setFont(smallfont)
        love.graphics.printf("Player: " .. tostring(servingPlayer) ..  "'s turn!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Serve!", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gamestate == 'victory' then
        -- draw victory message
        love.graphics.setFont(victoryFont)
        love.graphics.printf("Player " .. tostring(winningPlayer) ..  " wins!", 0, 10, VIRTUAL_WIDTH, 'center')
        love.graphics.setFont(smallfont)
        love.graphics.printf("Press Enter to Serve!", 0, 42, VIRTUAL_WIDTH, 'center')
    elseif gamestate == 'play' then
        -- no UI messages to display in play 
    end

    -- Ball render
    ball:render()

    -- Paddles render
    paddle1:render()
    paddle2:render()
 
    -- Score render
    displayScore()

    displayFPS()

    push:apply('end')    
end

-- function do  display FPS on the screen 
function displayFPS()
    love.graphics.setColor(0, 1, 0, 1)
    love.graphics.setFont(smallfont)
    love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 40, 20)
    love.graphics.setColor(1, 1, 1, 1)
end

--[[
    Simply draws the score to the screen
]]
function displayScore()
    -- draw score on the left and right center of the screen   
    -- switch the font before printing
    love.graphics.setFont(mediumfont)
    love.graphics.printf(tostring(player1Score), - 50, VIRTUAL_HEIGHT / 3, VIRTUAL_WIDTH, 'center')
    love.graphics.printf(tostring(player2Score), 50, VIRTUAL_HEIGHT / 3, VIRTUAL_WIDTH, 'center')
end


