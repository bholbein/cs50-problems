import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from datetime import datetime
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd, get_price, get_portfolio

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached

@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
db.execute("CREATE TABLE IF NOT EXISTs transactions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER, symbol VARCHAR NOT NULL, price REAL NOT NULL, shares INTEGER NOT NULL, method VARCHAR NOT NULL, time_stamp TEXT NOT NULL)")

# Global variables

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id = user_id)
    total = []
    total_buy_price = 0
    total_value = 0
    total_shares = 0
    portfolio = get_portfolio(db, user_id)
    if portfolio:         
        for element in portfolio:
            current_price = get_price(element['symbol'])
            value = element['SUM(shares)'] * current_price
            total_buy_price += element['SUM(shares * price)']
            total_value += value 
            total_shares += element['SUM(shares)']
            element.update({'price': current_price})
            element.update({'value': value })
            element.update({'diff': value - element['SUM(shares * price)']})
            element.update({'diff_percent': (value - element['SUM(shares * price)']) / element['SUM(shares * price)'] * 100 })
        total.append({'total_shares': total_shares, 'total_buy_price': total_buy_price, 'total_value': total_value, 'total_diff': total_value - total_buy_price, 'total_diff_percent': (total_value - total_buy_price)/total_buy_price * 100 }) 
    return render_template("index.html", portfolio=portfolio, cash = cash, total = total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        symbol = request.form.get("stock_symbol")
        shares = request.form.get('shares', type=int)
        if not symbol:
            return apology("Specify stock symbol", 403)
        elif (not shares) or (shares <= 0):
            return apology("Number of shares > 0", 403)
        user_id = session["user_id"]
        cash_before = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
        purchase = lookup(symbol)
        if not purchase:
            return apology("Stock not found")
        if cash_before[0]['cash'] < float(purchase['price']) * shares:
            return apology("Sorry, not enough cash")
        else:
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, method, time_stamp) values (:user_id, :symbol, :shares, :price, :method, :time)",
                       user_id=user_id, symbol=purchase['symbol'], shares=shares, price=purchase['price'], method="buy", time=datetime.now())
            cash_after = cash_before[0]['cash'] - (purchase['price'] * shares)
            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                       cash=cash_after, user_id=user_id)
        return render_template("bought.html", purchase=purchase, shares=shares, cash=cash_after)
    else:
        return apology("Invalid request type")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("stock_symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("could not find symbol", 403)
        else:
            return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Lookup username in the database
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username", username=username)
        if len(rows) == 1:
            return apology("username already exists", 403)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashed_pw)",
                       username=username, hashed_pw=generate_password_hash(password))
            rows = db.execute(
                "SELECT * FROM users WHERE username = :username", username=username)

            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        portfolio = get_portfolio(db, session["user_id"])
        return render_template("/sell.html", portfolio = portfolio)
    else:
        return render_template("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
