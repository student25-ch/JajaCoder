#!/usr/bin/env python3
# Copyright (C) 2026 JajaCoder-GUI Authors
# Licensed under GPLv3
import socket
from PySide6.QtWidgets import (QMainWindow, QWidget, QVBoxLayout,
                               QTextEdit, QLineEdit, QPushButton, QHBoxLayout)

def send_cmd(cmd:str):
    s = socket.socket()
    s.connect(("127.0.0.1",8899))
    s.sendall(cmd.encode('utf-8'))
    res = s.recv(4096).decode('utf-8')
    s.close()
    return res

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("JajaCoder-GUI")
        cw = QWidget()
        self.setCentralWidget(cw)
        lay = QVBoxLayout(cw)

        self.out = QTextEdit()
        self.out.setReadOnly(True)
        self.inp = QLineEdit()
        self.inp.setPlaceholderText("输入问题，或者先导入文本...")

        row = QHBoxLayout()
        self.btn_query = QPushButton("Query")
        self.btn_ingest = QPushButton("Ingest Text")
        self.btn_save = QPushButton("Save Index")
        self.btn_load = QPushButton("Load Index")
        row.addWidget(self.btn_query)
        row.addWidget(self.btn_ingest)
        row.addWidget(self.btn_save)
        row.addWidget(self.btn_load)

        lay.addWidget(self.out)
        lay.addWidget(self.inp)
        lay.addLayout(row)

        self.btn_query.clicked.connect(self.do_query)
        self.btn_ingest.clicked.connect(self.do_ingest)
        self.btn_save.clicked.connect(lambda:self.out.append(send_cmd("SAVE:")))
        self.btn_load.clicked.connect(lambda:self.out.append(send_cmd("LOAD:")))

    def do_query(self):
        q = self.inp.text().strip()
        if not q: return
        self.out.append(f"> Q: {q}")
        ret = send_cmd(f"QUERY:{q}")
        self.out.append(f"<< {ret}\n")
    def do_ingest(self):
        txt = self.inp.text().strip()
        if not txt: return
        self.out.append(f"> Ingest: {txt}")
        ret = send_cmd(f"INGEST:{txt}")
        self.out.append(f"<< {ret}\n")
