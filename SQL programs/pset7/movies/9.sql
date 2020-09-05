SELECT p.name
FROM people p
WHERE p.id IN (SELECT DISTINCT s.person_id
                FROM stars s
                JOIN movies m
                    ON m.id = s.movie_id
                WHERE m.year == 2004)
ORDER BY p.birth ASC, p.name ASC;