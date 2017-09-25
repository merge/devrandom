import time
with open('ed25519_signing_cert', 'rb') as f:
    x = f.read()
    print time.ctime(int(x[35:38].encode('hex'), 16) * 3600)
