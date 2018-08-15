import cv2 as cv


def mask_extractor(hsv, color):
    colors = {
        'red'  : [(0, 70, 50), (10, 255, 255), (170, 70, 50), (180, 255, 255)],
        'green': [(100, 20, 100), (255, 10, 255), (45, 100, 50), (90, 255, 255)],
        'black': []
    }

    mask1 = cv.inRange(hsv, colors[color][0], colors[color][1])
    mask2 = cv.inRange(hsv, colors[color][2], colors[color][3])
    return mask1 | mask2


def preprocessing():
    # gauss
    igm = cv.GaussianBlur(img)


if __name__ == '__main__':
    img = cv.imread('../../imgs/{}.jpg'.format('simple'))
    hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
