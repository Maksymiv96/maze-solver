resize_imgs:
	mogrify -resize 800x600 imgs/*/*.jpg

clear_cache:
	rm -r .pytest_cache && find . -name "*.pyc" -exec rm -f {} \

install_reqs:
	python -m pip install -r requirements.txt

