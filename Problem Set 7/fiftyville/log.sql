-- Query to find the id and description of the crime 
SELECT id, description 
  FROM crime_scene_reports 
 WHERE year = 2021 
   AND day = 28 
   AND month = 7 
   AND street = 'Humphrey Street'
   AND description LIKE '%CS50 duck%';

-- Query to find the three interviews regarding the bakery theft on 7/28/2021
SELECT * 
  FROM interviews 
 WHERE year = 2021 
   AND month = 7 
   AND day = 28 
   AND transcript LIKE '%bakery%';

-- Query to find all license plates of drivers who exited the bakery within 10 minutes of the theft, going off of lead from one of the interviews
SELECT licnese_plate 
  FROM bakery_security_logs 
 WHERE year = 2021 
   AND day = 28 
   AND month = 7 
   AND activity = 'exit' 
   AND hour = 10 
   AND (minute >= 15 AND minute <= 25);

-- Query of all Fiftyville callers with a duration under 60 seconds on the date of the bakery crime, going off of interview lead.
SELECT caller 
  FROM phone_calls 
 WHERE year = 2021 
   AND day = 28 
   AND month = 7 
   AND duration < 60;

-- Query to find all withdrawal transactions at the ATM on Leggett Street the day of the crime, going off of interview lead.
SELECT * 
  FROM atm_transactions 
 WHERE year = 2021 
   AND day = 28 
   AND month = 7 
   AND atm_location = 'Leggett Street' 
   AND transaction_type = 'withdraw';

-- Query to find the earliest flight out of Fiftyville the day after the crime at the bakery, going off of interview lead.
SELECT * 
  FROM flights 
 WHERE year = 2021 
   AND day = 29 
   AND month = 7 
   AND origin_airport_id IN 
        (SELECT id FROM airports WHERE city = 'Fiftyville') 
        ORDER BY hour ASC, minute ASC LIMIT 1;

 --Query to find the passport numbers of the passengers who were on the earliest flight out of Fiftyville on 7/29.
 SELECT passport_number 
   FROM passengers
  WHERE flight_id IN 
            (SELECT id 
               FROM flights 
              WHERE year = 2021 
                AND day = 29 
                AND month = 7 
                AND origin_airport_id IN 
                        (SELECT id FROM airports WHERE city = 'Fiftyville') 
                        ORDER BY hour ASC, minute ASC LIMIT 1);

-- Query to find person_ids associated with the account numbers from the withdrawals the day of the crime.
SELECT person_id 
  FROM bank_accounts 
 WHERE account_number IN 
    (SELECT account_number 
       FROM atm_transactions 
      WHERE year = 2021 
        AND day = 28 
        AND month = 7 
        AND atm_location = 'Leggett Street' 
        AND transaction_type = 'withdraw');

-- The grand daddy query of them all! To find the culprit based on cross referencing his license plate, passport, and phone number in prior queries.
SELECT * FROM people WHERE id IN (SELECT person_id 
  FROM bank_accounts 
 WHERE account_number IN 
        (SELECT account_number 
           FROM atm_transactions 
          WHERE year = 2021 
            AND day = 28 
            AND month = 7 
            AND atm_location = 'Leggett Street' 
            AND transaction_type = 'withdraw'))
    AND passport_number IN
            (SELECT passport_number 
               FROM passengers
              WHERE flight_id IN 
                        (SELECT id 
                           FROM flights 
                          WHERE year = 2021 
                            AND day = 29 
                            AND month = 7 
                            AND origin_airport_id IN 
                                    (SELECT id 
                                       FROM airports WHERE city = 'Fiftyville') 
                                    ORDER BY hour ASC, minute ASC LIMIT 1))
    AND phone_number IN
            (SELECT caller 
               FROM phone_calls 
              WHERE year = 2021 
                AND day = 28 
                AND month = 7 
                AND duration < 60)
    AND license_plate IN
            (SELECT license_plate 
               FROM bakery_security_logs 
              WHERE year = 2021 
                AND day = 28 
                AND month = 7 
                AND activity = 'exit' 
                AND hour = 10 
                AND (minute >= 15 AND minute <= 25));

-- Query to find which city the culprit flew to.
SELECT city 
  FROM airports 
 WHERE id IN 
        (SELECT destination_airport_id 
        FROM flights 
        WHERE id IN 
                (SELECT flight_id 
                   FROM passengers 
                  WHERE passport_number IN 
                        (SELECT passport_number FROM people WHERE id IN (SELECT person_id 
                           FROM bank_accounts 
                          WHERE account_number IN 
                                    (SELECT account_number 
                                       FROM atm_transactions 
                                      WHERE year = 2021 
                                        AND day = 28 
                                        AND month = 7 
                                        AND atm_location = 'Leggett Street' 
                                        AND transaction_type = 'withdraw'))
                                AND passport_number IN
                                        (SELECT passport_number 
                                           FROM passengers
                                          WHERE flight_id IN 
                                                    (SELECT id 
                                                       FROM flights 
                                                      WHERE year = 2021 
                                                        AND day = 29 
                                                        AND month = 7 
                                                        AND origin_airport_id IN 
                                                                (SELECT id 
                                                                   FROM airports WHERE city = 'Fiftyville') 
                                                   ORDER BY hour ASC, minute ASC LIMIT 1))
                                AND phone_number IN
                                        (SELECT caller 
                                           FROM phone_calls 
                                          WHERE year = 2021 
                                            AND day = 28 
                                            AND month = 7 
                                            AND duration < 60)
                                AND license_plate IN
                                        (SELECT license_plate 
                                           FROM bakery_security_logs 
                                          WHERE year = 2021 
                                            AND day = 28 
                                            AND month = 7 
                                            AND activity = 'exit' 
                                            AND hour = 10 
                                            AND (minute >= 15 AND minute <= 25)))));

-- Query to find who the accomplice who bought the culprit's ticket was.
SELECT * 
  FROM people 
 WHERE phone_number IN
        (SELECT receiver 
           FROM phone_calls
          WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
            AND caller IN 
                    (SELECT phone_number FROM people WHERE id IN (SELECT person_id 
                       FROM bank_accounts 
                      WHERE account_number IN 
                            (SELECT account_number 
                               FROM atm_transactions 
                              WHERE year = 2021 
                                AND day = 28 
                                AND month = 7 
                                AND atm_location = 'Leggett Street' 
                                AND transaction_type = 'withdraw'))
                        AND passport_number IN
                                (SELECT passport_number 
                                   FROM passengers
                                  WHERE flight_id IN 
                                            (SELECT id 
                                               FROM flights 
                                              WHERE year = 2021 
                                                AND day = 29 
                                                AND month = 7 
                                                AND origin_airport_id IN 
                                                        (SELECT id 
                                                           FROM airports WHERE city = 'Fiftyville') 
                                             ORDER BY hour ASC, minute ASC LIMIT 1))
                        AND phone_number IN
                                (SELECT caller 
                                   FROM phone_calls 
                                  WHERE year = 2021 
                                    AND day = 28 
                                    AND month = 7 
                                    AND duration < 60)
                        AND license_plate IN
                                (SELECT license_plate 
                                   FROM bakery_security_logs 
                                  WHERE year = 2021 
                                    AND day = 28 
                                    AND month = 7 
                                    AND activity = 'exit' 
                                    AND hour = 10 
                                    AND (minute >= 15 AND minute <= 25))));