import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)

    # Getting my transactions
    my_transactions = db.execute("""
    SELECT *
    FROM transactions
    WHERE buyer_id = ?;
    """, (user_id,))

    # Getting quantity of shares by item
    portfolio = {}
    for transaction in my_transactions:
        if transaction['type'] == 'buy': # Buy case
            if transaction['symbol'] in portfolio:
                portfolio[transaction['symbol']] += transaction['shares']
            else:
                portfolio[transaction['symbol']] = transaction['shares']
        else: # Sell case
            if transaction['symbol'] in portfolio:
                portfolio[transaction['symbol']] -= transaction['shares']
            else:
                portfolio[transaction['symbol']] = - transaction['shares']

    # Calcula o valor total de cada ação e armazena no dicionário total_value
    for symbol, quantity in portfolio.items():
        # Obtém o preço atual da ação usando a função lookup
        price = lookup(symbol)['price']
        # Calcula o valor total para o símbolo
        total_amount = quantity * price
        # Armazena o valor total e a quantidade de ações no dicionário total_value
        portfolio[symbol] = {
            'total_shares': quantity,
            'total_value': total_amount
        }




    # Getting total money
    total_price = user[0]['cash']
    for symbol, quantity in portfolio.items():
        # Obtém o preço atual da ação usando a função lookup
        total_price += portfolio[symbol]['total_value']

    return render_template("index.html", user=user[0], portfolio=portfolio, total_price=total_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("You must provide a symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("You must provide a positive number of shares", 400)

        # Verifying if the symbol is valid
        quote = lookup(symbol)
        if quote is None:
            return apology("Symbol not found", 400)


        # Getting total cost
        cost = int(shares) * quote['price']

        # Getting user info
        user_id = session["user_id"]
        user_data = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        previous_portfolio = user_data[0]['cash']

        # Verifying if the user has enough money
        if cost > previous_portfolio:
            return apology("You don't have enough money to buy this quantity of shares", 400)



        # Deducting the cost from user's cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)

        # Getting current time
        now = datetime.now()

        # Adding into database
        db.execute("""
            INSERT INTO transactions (buyer_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, ?)
            """,
            user_id, symbol, shares, cost, "buy",
        )
        flash(f"Bought {shares} shares of {symbol} for {usd(cost)}")
        # Redirect user to home page
        return redirect("/")
    else:
        user_id = session["user_id"]
        user_data = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        return render_template("buy.html", user_data=user_data[0])

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("""
        SELECT *
        FROM transactions
        WHERE buyer_id = ?
        ORDER BY timestamp DESC;
        """, (user_id,))

    # Changing transactions to tymestamp
    for transaction in transactions:
        transaction['timestamp'] = datetime.strptime(transaction['timestamp'], '%Y-%m-%d %H:%M:%S')
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not quote:
            return apology("Invalid symbol.", 400)
        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Getting username, password, and confirm password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Verifying if username is provided
        if not username:
            return apology("Must provide username", 400)

        # Verifying if password is provided
        elif not password:
            return apology("Must provide password", 400)

        # Verifying if password is provided
        elif not confirmation:
            return apology("Must confirm password", 400)

        # Verifying if passwords match
        elif password != confirmation:
            return apology("Passwords do not match", 400)

        # Verifying if user already exists
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", username
        )

        # Ensure username exists and password is correct
        if len(rows) != 0:
            return apology("User already exist!", 400)

        # Creating a hash password
        hash_password = generate_password_hash(password)

        # Adding user to the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hash_password
        )

        # Getting user_id
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]['id']

        # Remember which user has logged in
        session["user_id"] = user_id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        user_data = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Getting my transactions
        portfolio = db.execute("""
        SELECT symbol,
            SUM(shares) AS total_shares,
            SUM(price) AS total_price
        FROM transactions
        WHERE buyer_id = ?
        GROUP BY symbol;
        """, (user_id,))

        return render_template("sell.html", user=user_data[0], portfolio=portfolio)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Please enter a symbol!", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Please enter a positive number of shares!", 400)

        # User info
        user_id = session["user_id"]

        # Getting total shares for a specific symbol and user
        transactions = db.execute("""
        SELECT *
        FROM transactions
        WHERE buyer_id = ? AND symbol = ?;
        """,user_id, symbol)

        total_shares = 0
        # Getting actual quantity of shares
        for t in transactions:
            print(t['type'])
            if t['type'] == 'buy':
                total_shares += t['shares']
            else:
                total_shares -= t['shares']
        print(total_shares)
        # Verifying if user has enought shares to sell
        if total_shares <= 0 or total_shares < int(shares):
            return apology("You don't have enough shares!", 400)

        # Obtém o preço atual da ação usando a função lookup
        price_per_share = lookup(symbol)['price']

        # Getting the final cost
        cost = int(shares) * price_per_share

        # Adding funds into users, count
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cost, user_id)

        # Adding into database
        db.execute("""
            INSERT INTO transactions (buyer_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, ?)
            """,
            user_id, symbol, shares, cost, "sell",
        )
        return redirect("/")
