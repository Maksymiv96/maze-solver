import cv2 as cv

IMG_PATH = '../../imgs/{}.jpg'

img = cv.imread(IMG_PATH.format('simple'))

img += 64
img = img / 1.5
cv.imshow("Image", img)
cv.waitKey(0)
cv.destroyAllWindows()
