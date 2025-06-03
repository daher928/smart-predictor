# Smart Predictor

This repository contains a small C++ project that reads lottery results from `Data.csv` and allows you to check if a new guess already exists in the history.

A simple FastAPI application (`app.py`) exposes this functionality via an HTTP endpoint.

## Running the API

1. Install dependencies (preferably in a virtual environment):

```bash
pip install -r requirements.txt
```

2. Start the server:

```bash
uvicorn app:app --reload
```

3. Send a POST request to `/check` with a JSON body:

```json
{
  "numbers": [1, 2, 3, 4, 5, 6],
  "additional": 6
}
```

The response will contain `{"exists": true}` if the numbers appear in `Data.csv`.
