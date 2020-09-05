SELECT p.name
FROM people p
WHERE p.id != (SELECT p.id
               FROM people p
               WHERE p.name = 'Kevin Bacon'
                   AND p.birth = 1958)
    AND p.id IN (SELECT DISTINCT p.id
                 FROM people p
                 JOIN stars s
                    ON p.id = s.person_id
                 WHERE s.movie_id IN (SELECT m.id
                                      FROM movies m
                                      JOIN stars s
                                          ON s.movie_id = m.id
                                      JOIN people p
                                          ON s.person_id = p.id
                                      WHERE p.name = 'Kevin Bacon' 
                                          AND p.birth = 1958));