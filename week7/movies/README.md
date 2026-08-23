# Movies

SQL queries for the **CS50 SQL Movies** problem set.

The queries were written and tested using the `movies.db` database provided by CS50, which contains data from IMDb. The database itself is not included in this repository because of its size.

## Database Schema

The database contains five tables:

### `movies`

Contains information about movies.

| Column  | Type    | Description             |
| ------- | ------- | ----------------------- |
| `id`    | INTEGER | Unique movie identifier |
| `title` | TEXT    | Movie title             |
| `year`  | NUMERIC | Year of release         |

### `people`

Contains information about people involved in movies.

| Column  | Type    | Description              |
| ------- | ------- | ------------------------ |
| `id`    | INTEGER | Unique person identifier |
| `name`  | TEXT    | Person's name            |
| `birth` | NUMERIC | Year of birth            |

### `stars`

Connects people with the movies they starred in.

| Column      | Type    | Description            |
| ----------- | ------- | ---------------------- |
| `movie_id`  | INTEGER | References `movies.id` |
| `person_id` | INTEGER | References `people.id` |

### `directors`

Connects people with the movies they directed.

| Column      | Type    | Description            |
| ----------- | ------- | ---------------------- |
| `movie_id`  | INTEGER | References `movies.id` |
| `person_id` | INTEGER | References `people.id` |

### `ratings`

Contains ratings and vote counts for movies.

| Column     | Type    | Description            |
| ---------- | ------- | ---------------------- |
| `movie_id` | INTEGER | References `movies.id` |
| `rating`   | REAL    | Movie rating           |
| `votes`    | INTEGER | Number of votes        |

## Relationships

The main relationships between the tables are:

```text
people
  │
  ├───────────────┐
  │               │
  ▼               ▼
stars          directors
  │               │
  └───────┬───────┘
          │
          ▼
        movies
          │
          ▼
       ratings
```

* `stars.movie_id` → `movies.id`
* `stars.person_id` → `people.id`
* `directors.movie_id` → `movies.id`
* `directors.person_id` → `people.id`
* `ratings.movie_id` → `movies.id`

The `stars` and `directors` tables act as connections between `people` and `movies`.

## Files

The repository contains the 13 SQL queries from the problem set:

* `1.sql` — `13.sql`

The original `movies.db` database is not included due to its size.
