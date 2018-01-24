
PYVENV = pyvenv-3.4 --without-pip
  
install:
	# pyvenv-3.4 env ### BUGGY on ix
	$(PYVENV)  env
	make env/bin/pip
	(.  env/bin/activate; pip install -r requirements.txt)

env/bin/pip: env/bin/activate
	echo ""
	(.  env/bin/activate; curl https://bootstrap.pypa.io/get-pip.py | python)


dist:
	pip freeze >requirements.txt
