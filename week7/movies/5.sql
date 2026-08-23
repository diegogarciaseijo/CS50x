-- 5. Titles and years of all Harry Potter movies, in chronological order (title beginning with "Harry Potter and the ...")
SELECT title, year
FROM movies
where title LIKE "%Harry Potter and the%"
ORDER BY year ASC;
