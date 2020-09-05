SELECT p.name
FROM people p
WHERE p.id IN (SELECT DISTINCT d.person_id 
                FROM directors d
                JOIN ratings r
                    ON r.movie_id = d.movie_id
                WHERE rating >= 9.0)
ORDER BY p.name ASC;