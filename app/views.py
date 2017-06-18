import os
from flask import render_template,request,redirect, url_for
from werkzeug.utils import secure_filename
from cifa import cifa
from app import app


UPLOAD_FOLDER = 'app/static/Uploads'
fname = ""

@app.route('/upload', methods=['GET', 'POST'])
def upload():
    f = request.files['source']
    fname = secure_filename(f.filename) #获取一个安全的文件名，且仅仅支持ascii字符；
    if fname == '':
        return redirect(url_for('index'))
    f.save(os.path.join(UPLOAD_FOLDER, fname))
    return redirect(url_for('cindex', fname=fname))

@app.route('/',methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return redirect(url_for('index'))
    return render_template("index.html")

@app.route('/<fname>',  methods=['GET', 'POST'])
def cindex(fname):
    if request.method == 'POST':
        r_the_text = request.form['r_text']
        cifa1 = cifa(r_the_text)
        cifa1.Start_convert()
        char_message = cifa1.Get_char()
        error_message = cifa1.Get_error()
        for token in char_message:
            token[0] = "<tr><td width = \"%30\">"+token[0]+"</td>"
            token[1] = "<td width = \"%70\">" + token[1] + "</td></tr>"
        for error in error_message:
            error[0] = "<tr><td width = \"%30\">" + error[0] + "</td>"
            error[1] = "<td width = \"%70\">" + error[1] + "</td></tr>"
        r_char_message = ''
        r_error_message = ''
        for i in char_message:
            for j in i:
                r_char_message = r_char_message + j
        for i in error_message:
            for j in i:
                r_error_message = r_error_message + j
        # print(r_the_text)
        return render_template("index.html",all_the_text = r_the_text,r_char_message = r_char_message,r_error_message = r_error_message)
    if request.method == 'GET' and fname == "favicon.ico":
        return "top.jpg"
    if request.method == 'GET' and fname != "favicon.ico":
        all_the_text = open(os.path.join(UPLOAD_FOLDER, fname)).read()
        return render_template("index.html", all_the_text=all_the_text)