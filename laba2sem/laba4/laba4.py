#чертежник
import numpy as np

EPS = 1e-9  # точность для сравнения float

#Проверка: точка лежит на прямой
def is_point_on_line(P, A, B):
    # косое произведение векторов AP и AB
    val = (P[0]-A[0])*(B[1]-A[1]) - (P[1]-A[1])*(B[0]-A[0])
    return abs(val) < EPS

# Проверка: пересекаются ли две прямые
def do_lines_intersect(A1, A2, B1, B2):
    v1 = np.array(A2) - np.array(A1)  # вектор первой прямой
    v2 = np.array(B2) - np.array(B1)  # вектор второй прямой
    det = v1[0]*v2[1] - v1[1]*v2[0]  # косое произведение (определитель)

    if abs(det) > EPS:
        return "Пересекаются (одна точка)"
    else:
        if is_point_on_line(A1, B1, B2):
            return "Совпадают (бесконечно много точек)"
        else:
            return "Параллельны (не пересекаются)"

# Проверка выпуклости многоугольника
def check_convexity(points):
    n = len(points)
    if n < 3:
        return "Это не многоугольник"

    pts = np.vstack([points, points[:2]])  # замкнуть цикл
    signs = []

    for i in range(n):
        v1 = pts[i+1] - pts[i]
        v2 = pts[i+2] - pts[i+1]
        cp = v1[0]*v2[1] - v1[1]*v2[0]  # косое произведение
        if abs(cp) > EPS:
            signs.append(cp > 0)

    return "Выпуклый" if all(signs) or not any(signs) else "Впуклый (невыпуклый)"

#Сколько раз пересекаются две окружности
def circle_intersections(c1, r1, c2, r2):
    d = np.linalg.norm(np.array(c1) - np.array(c2))  # расстояние между центрами

    if abs(d) < EPS and abs(r1 - r2) < EPS:
        return "Бесконечно много (совпадают)"
    if d > r1 + r2 + EPS or d < abs(r1 - r2) - EPS:
        return 0
    if abs(d - (r1 + r2)) < EPS or abs(d - abs(r1 - r2)) < EPS:
        return 1
    return 2

#тесты
print("1) Точка на прямой:", is_point_on_line([5,5], [0,0], [10,10]))

print("\n2) Пересечение прямых:", do_lines_intersect([0,0],[1,1],[0,1],[1,0]))

square = np.array([[0,0],[5,0],[5,5],[0,5]])
L_shape = np.array([[0,0],[5,0],[5,2],[2,2],[2,5],[0,5]])
print("\n3) Многоугольники:")
print("Квадрат:", check_convexity(square))
print("L-образный:", check_convexity(L_shape))

print("\n4) Окружности:", circle_intersections([0,0],5,[7,0],5))
