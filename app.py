"""HTTP API for verifying historical lottery numbers.

The module exposes a single endpoint ``/check`` that accepts a list of six
numbers and an additional number.  The numbers are compared with the historical
results stored in ``Data.csv`` which lives next to this file.
"""

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List
import csv
from pathlib import Path

ARCHIVE_FILE = Path(__file__).resolve().parent / "Data.csv"

class Guess(BaseModel):
    """Request body describing a lottery guess."""

    numbers: List[int]
    additional: int

app = FastAPI(title="Smart Predictor API")

# In-memory list of previously drawn numbers.  Each entry contains six sorted
# numbers followed by the additional number.
results_history: List[List[int]] = []

def load_archive() -> None:
    """Populate ``results_history`` from ``Data.csv``.

    The first row of the file is skipped as it contains column labels.
    Each subsequent row consists of seven comma separated integers.
    """

    global results_history
    results_history.clear()
    with ARCHIVE_FILE.open(newline="") as f:
        reader = csv.reader(f)
        # Discard header row
        _ = next(reader, None)
        for row in reader:
            results_history.append([int(x) for x in row])

load_archive()


def validate_numbers(nums: List[int]) -> bool:
    """Return ``True`` if ``nums`` contains valid lottery numbers.

    ``nums`` must contain exactly seven integers: six main numbers in the range
    ``1``-``37`` and a seventh additional number in the range ``1``-``6``.
    """

    if len(nums) != 7:
        return False
    numbers = nums[:6]
    additional = nums[6]
    if not (1 <= additional <= 6):
        return False
    return all(1 <= n <= 37 for n in numbers)


def check_exists(nums: List[int]) -> bool:
    """Check if ``nums`` is present in ``results_history``."""

    sorted_nums = sorted(nums[:6]) + [nums[6]]
    return sorted_nums in results_history


@app.post("/check")
def check_guess(guess: Guess):
    """Endpoint that reports if a guess appears in ``Data.csv``."""

    numbers = guess.numbers
    additional = guess.additional
    if len(numbers) != 6:
        raise HTTPException(status_code=400, detail="Exactly 6 numbers required")
    combo = numbers + [additional]
    if not validate_numbers(combo):
        raise HTTPException(status_code=400, detail="Invalid numbers")
    exists = check_exists(combo)
    return {"exists": exists}
