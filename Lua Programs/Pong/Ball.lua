Ball = Class{}

function Ball:init(x, y, width, height)
    self.x = x
    self.y = y 
    self.width = width
    self.height = height

    -- Used to get the speed for ball movement in x and y 
    self.dx = math.random(2) == 1 and 100 or -100
    self.dy = math.random(50, -50)
end

function Ball:collides(box)
    if self.x > box.x + box.width or self.x + self.width < box.x then
        return false
    end

    if self.y > box.y + box.height or self.y + self.height < box.y then
        return false
    end

    return true
end

function Ball:update(dt)
    self.x = self.x + self.dx * dt
    self.y = self.y + self.dy * dt
end

function Ball:reset()
    -- Start out ball's postiion
    self.x = VIRTUAL_WIDTH / 2 - 2
    self.y = VIRTUAL_HEIGHT / 2 -2

    -- given ball's x and y velocity a random starting value
    self.dx = math.random(2) == 1 and 100 or -100
    self.dy = math.random(50, -50) * 1.5
end

function Ball:render()
    love.graphics.rectangle('fill', self.x, self.y, 4, 4)
end