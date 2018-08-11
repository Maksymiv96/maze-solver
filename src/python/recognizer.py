import cv2 as cv


COLORS_DIR = {
    'red': [(0, 70, 50), (10, 255, 255), (170, 70, 50), (180, 255, 255)],
    'green': [(100, 20, 100), (255, 10, 255), (45, 100, 50), (90, 255, 255)],
    'black': []
}


def mask_by_color(hsv, color):
    mask1 = cv.inRange(hsv, COLORS_DIR[color][0], COLORS_DIR[color][1])
    mask2 = cv.inRange(hsv, COLORS_DIR[color][2], COLORS_DIR[color][3])
    return mask1 | mask2


if __name__ == '__main__':
    img = cv.imread('../../imgs/{}.jpg'.format('simple'))

    hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    red_mask, green_mask = mask_by_color(hsv, 'red'), mask_by_color(hsv, 'green')
    masked_img = cv.bitwise_not(img, img,
                                mask=cv.bitwise_or(red_mask, green_mask))

    cv.imshow('w', masked_img)
    cv.waitKey(0)
    cv.destroyAllWindows()
