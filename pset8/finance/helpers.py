import os
import urllib.parse
import requests

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(
            f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def get_price(symbol) -> float:
    quote = lookup(symbol)
    return quote['price']


def get_cash(db, user_id) -> float:
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
    return cash[0]['cash']


def update_cash(db, user_id, cash) -> bool:
    """updates cash in database for specific user

    Args:
        db ([obj]): [data base connection]
        user_id ([int]): [ID of specific user should match database]
        cash ([float]): [new cash amount to be set]

    Returns:
        bool: [true if succesfull else false]
    """
    try:
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                   cash=cash, user_id=user_id)
        session["cash"] = cash
        return True
    except RuntimeError:
        return False


def get_portfolio(db, user_id) -> dict:
    try:
        portfolio = db.execute("SELECT symbol, SUM(shares) as shares, SUM(shares * price) as share_value FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=user_id)
        return portfolio
    except RuntimeError:
        print("Could not get portfolio")

def get_transactions(db, user_id) -> dict:
    try:
        transactions = db.execute("SELECT time_stamp, symbol, shares, price, shares * price as value, method FROM transactions WHERE user_id=:user_id ORDER BY time_stamp DESC", user_id = user_id)
        return transactions
    except RuntimeError:
        print("Could not fetch transactions from database.s")