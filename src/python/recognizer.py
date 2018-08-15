import cv2 as cv





if __name__ == '__main__':
    img = cv.imread('../../imgs/{}.jpg'.format('simple'))

    hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    red_mask, green_mask = mask_by_color(hsv, 'red'), mask_by_color(hsv, 'green')
    masked_img = cv.bitwise_not(img, img,
                                mask=cv.bitwise_or(red_mask, green_mask))

    cv.imshow('w', masked_img)
    cv.waitKey(0)
    cv.destroyAllWindows()
