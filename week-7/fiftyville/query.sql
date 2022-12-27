 SELECT *
 FROM people, passengers
 WHERE passengers.passport_number IN (
    SELECT passport_number
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND day = 28
        AND month = 07
        AND hour = 10
        AND minute < 25
        AND activity = "exit"
        )
    AND phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021
        AND month = 07
        AND day = 28
        AND duration < 60
        )
    AND id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number
        IN (
            SELECT account_number
            FROM atm_transactions
            WHERE atm_location
            LIKE "Leggett Street"
            AND year = 2021
            AND month = 7
            AND day = 28
            )
        )
    )
    AND passengers.flight_id = 36
    AND people.passport_number = passengers.passport_number;