-- Keep a log of any SQL queries you execute as you solve the mystery.
 -- Get information from the crime scene looking at what exactly happened that day

SELECT *
FROM crime_scene_reports
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND street = "Humphrey Street";

-- After knowing that the theft took place at 10:15am at the bakery, I check the bakery security logs for around that time

SELECT *
FROM bakery_security_logs
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND HOUR = 10;

-- I saw that there was an entrance at 10:14 and an exit at 10:16, perfect for a theft at 10:15, but the license plate doesn't match, so I'll see what the witness said

SELECT *
FROM interviews
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28;

-- I got a lot of information from the witnesses. The thief drove away with a car from the bakery parking lot, was withdrawing money at the ATM on Leggett Street that morning, and has an accomplice who is buying both of them a flight out of town tomorrow.
 -- I'll firstly check the ATM

SELECT *
FROM atm_transactions
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw";

-- There are 8 withdrawals at that ATM that day. I don't think I can use that information right now, so I'll check the phone calls with the accomplice

SELECT *
FROM phone_calls
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28;

-- There are a lot of calls, so I don't think I can use that information right now. I'll check the flight they bought for the next day

SELECT *
FROM flights
WHERE origin_airport_id =
        (SELECT id
         FROM airports
         WHERE city = "Fiftyville")
    AND YEAR = 2025
    AND MONTH = 7
    AND DAY = 29;

-- The witness said that they were leaving the city on the first flight, so it has to be the 8:20 one, with ID 36. I'll check its passengers

SELECT *
FROM passengers
WHERE flight_id = 36;

-- There are 8 people on that flight. I'll see who they are

SELECT *
FROM people
WHERE passport_number IN
        (SELECT passport_number
         FROM passengers
         WHERE flight_id = 36);

-- I'll now check if any of their phone numbers matches the calls that day

SELECT *
FROM phone_calls
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND caller IN
        (SELECT phone_number
         FROM people
         WHERE passport_number IN
                 (SELECT passport_number
                  FROM passengers
                  WHERE flight_id = 36))
    AND receiver IN
        (SELECT phone_number
         FROM people
         WHERE passport_number IN
                 (SELECT passport_number
                  FROM passengers
                  WHERE flight_id = 36));

-- I now have only 2 phone numbers. Those are (826) 555-9701 and (066) 555-9701. I now just have to figure out which one is each of them
 -- I'll check which one of them was around the bakery at the time of the theft

SELECT *
FROM bakery_security_logs
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND HOUR = 10
    AND license_plate IN
        (SELECT license_plate
         FROM people
         WHERE phone_number = "(826) 555-9701"
             OR phone_number = "(066) 555-9701");

-- I got the name "Doris", so she is the main suspect for now
 -- I'll now check if she was at the ATM that day to be more sure

SELECT *
FROM atm_transactions
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND account_number =
        (SELECT account_number
         FROM bank_accounts
         WHERE person_id =
                 (SELECT id
                  FROM people
                  WHERE name = "Doris"));

-- Doris wasn't at the ATM, so she can't be the thief. But her car left the bakery at the time of the robbery. Is she the accomplice and did she lend her car to the thief, or did the thief just steal it from her?
 -- I'll check if any of the people on the flight was at the ATM that day

SELECT *
FROM atm_transactions
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND account_number IN
        (SELECT account_number
         FROM bank_accounts
         WHERE person_id =
                 (SELECT id
                  FROM people
                  WHERE passport_number IN
                          (SELECT passport_number
                           FROM passengers
                           WHERE flight_id = 36)));

-- I saw that someone with account number 28296815 matches. Let's see who that person is

SELECT *
FROM people
WHERE id =
        (SELECT person_id
         FROM bank_accounts
         WHERE account_number = 28296815);

-- That person's name is Kenny, but her phone number doesn't match one of the two passengers on the flight who had a call between each other. Maybe she isn't involved in the flight and she just bought it for the thief?
 -- Let's see if she had any calls on the day of the crime

SELECT *
FROM phone_calls
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND (receiver = "(826) 555-1652"
         OR caller = "(826) 555-1652");

-- Yes, she had a call that day with someone with phone number (066) 555-9701. Let's see who that is

SELECT *
FROM people
WHERE phone_number = "(066) 555-9701";

-- That's Doris again, so we can assume now that she is the accomplice and Kenny is the thief
 -- Let's finally check where their flight is going

SELECT *
FROM airports
WHERE id =
        (SELECT destination_airport_id
         FROM flights
         WHERE YEAR = 2025
             AND MONTH = 7
             AND DAY = 29
             AND HOUR = 8
             AND MINUTE = 20);

-- That gives us New York City, so that's where the thief escaped to
 -- My first theory was wrong, but I'm pretty certain that the city is New York because that's the first flight of the day. I'll check again all the people from the flight

SELECT *
FROM people
WHERE passport_number IN
        (SELECT passport_number
         FROM passengers
         WHERE flight_id =
                 (SELECT id
                  FROM flights
                  WHERE YEAR = 2025
                      AND MONTH = 7
                      AND DAY = 29
                      AND HOUR = 8
                      AND MINUTE = 20));

-- There are 8 people on the flight. I'll investigate the remaining candidates again instead of assuming that Kenny and Doris are involved
 -- I'll check which of the remaining passengers made a withdrawal at the ATM

SELECT *
FROM atm_transactions
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND account_number IN
        (SELECT account_number
         FROM bank_accounts
         WHERE person_id IN
                 (SELECT id
                  FROM people
                  WHERE name = "Sofia"
                      OR name = "Taylor"
                      OR name = "Luca"
                      OR name = "Kelsey"
                      OR name = "Edward"
                      OR name = "Bruce"));

-- I now have 3 account numbers that were used at the ATM: 28500762, 76054385 and 49610011. I'll check who they belong to

SELECT *
FROM people
WHERE id IN
        (SELECT person_id
         FROM bank_accounts
         WHERE account_number = 28500762
             OR account_number = 76054385
             OR account_number = 49610011);

-- These are Taylor, Luca and Bruce. I'll check which of them had a car at the bakery around the time of the robbery

SELECT *
FROM people
WHERE (name = "Taylor"
       OR name = "Luca"
       OR name = "Bruce")
    AND license_plate IN
        (SELECT license_plate
         FROM bakery_security_logs
         WHERE YEAR = 2025
             AND MONTH = 7
             AND DAY = 28
             AND HOUR = 10);

-- Now I have the candidates whose cars appeared at the bakery. I'll check their calls that lasted less than one minute that day

SELECT *
FROM phone_calls
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND duration < 60
    AND (caller IN
             (SELECT phone_number
              FROM people
              WHERE name = "Taylor"
                  OR name = "Luca"
                  OR name = "Bruce")
         OR receiver IN
             (SELECT phone_number
              FROM people
              WHERE name = "Taylor"
                  OR name = "Luca"
                  OR name = "Bruce"));

-- I now need to combine the ATM, bakery and phone call clues instead of assuming that the first candidate who matches one clue is the thief
 -- The witness said that the thief left the bakery within ten minutes of the theft. The theft happened at 10:15, so I'll check the cars that left between 10:15 and 10:25

SELECT *
FROM bakery_security_logs
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND HOUR = 10
    AND MINUTE >= 15
    AND MINUTE <= 25
    AND activity = "exit";

-- Bruce's car left at 10:18 and Luca's car left at 10:19, while Taylor's car left later. I'll investigate the remaining two candidates
 -- I'll check which of Bruce and Luca had a phone call lasting less than one minute

SELECT *
FROM phone_calls
WHERE YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND duration < 60
    AND (caller IN
             (SELECT phone_number
              FROM people
              WHERE name = "Bruce"
                  OR name = "Luca")
         OR receiver IN
             (SELECT phone_number
              FROM people
              WHERE name = "Bruce"
                  OR name = "Luca"));

-- Bruce had a short call that matches the witness's description. I'll check who he called

SELECT *
FROM phone_calls
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration < 60
    AND
        (caller =
            (SELECT phone_number
            FROM people
            WHERE name = "Bruce")
        OR receiver =
            (SELECT phone_number
            FROM people
            WHERE name = "Bruce"));

-- The short call was with the phone number. I'll see who it belongs to

SELECT *
FROM people
WHERE phone_number = "(375) 555-8161";

-- The person Bruce called was Robin, so Bruce is the thief and Robin is the accomplice
