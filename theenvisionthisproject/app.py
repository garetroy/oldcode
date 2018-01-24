
import flask, os, json
from flask import render_template, jsonify, Flask, request, url_for
app = flask.Flask(__name__)

@app.route('/index')
@app.route('/')
@app.route('/home')
def index():
	return flask.render_template('wateruse.html')

if __name__ == '__main__':
	port = int(os.environ.get('PORT', 5000))
	app.run(debug=True, host='0.0.0.0', port=port)