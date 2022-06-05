import math, random

f = open("uranus.xml", 'w')

angle = 0
inc = 2 * math.pi / 27
radius = 10
random.seed(20)

def scale(i):
    if i == 14:
        f.write('\t\t\t\t\t\t\t<scale x="0.10" y="0.10" z="0.10" />\n')
    elif i in [15, 16]:
        f.write('\t\t\t\t\t\t\t<scale x="0.30" y="0.30" z="0.30" />\n')
    elif i in [17, 18]:
        f.write('\t\t\t\t\t\t\t<scale x="0.40" y="0.40" z="0.40" />\n')
    else:
        f.write('\t\t\t\t\t\t\t<scale x="0.05" y="0.05" z="0.05" />\n')

def buildTranslate(i, x, y, z):
    args = [0, 0, 0, 0]
    if i % 2 == 0:
        args[0] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y[0])}" z="0"/>\n'
        args[1] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(y[1])}" z="{"{:.2f}".format(z)}"/>\n'
        args[2] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(-x)}" y="{"{:.2f}".format(-y[0])}" z="0"/>\n'
        args[3] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(y[1])}" z="{"{:.2f}".format(-z)}"/>\n'
    else:
        args[0] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(y[1])}" z="{"{:.2f}".format(z)}"/>\n'
        args[1] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y[0])}" z="0"/>\n'
        args[2] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(-y[1])}" z="{"{:.2f}".format(-z)}"/>\n'
        args[3] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(-x)}" y="{"{:.2f}".format(y[0])}" z="0"/>\n'
    return args

def translate(i, time, args):
    i1 = i % 4
    i2 = (i1 + 1) % 4
    i3 = (i1 + 2) % 4
    i4 = (i1 + 3) % 4

    f.write(f'\t\t\t\t\t\t\t<translate time = "{time}" align="False">\n')
    f.write(args[i1])
    f.write(args[i2])
    f.write(args[i3])
    f.write(args[i4])
    f.write('\t\t\t\t\t\t\t</translate>\n')

def color(i):
    f.write('\t\t\t\t\t\t\t\t<color>\n')
    f.write('\t\t\t\t\t\t\t\t<diffuse R="200" G="200" B="200" />')
    f.write('<ambient R="200" G="200" B="200" />')
    f.write('<specular R="250" G="250" B="250" />')
    f.write('<emissive R="0" G="0" B="0" />')
    f.write('<shininess value="127" />\n')
    f.write('\t\t\t\t\t\t\t\t</color>\n')

def texture(i):
    if i == 14:
        f.write('\t\t\t\t\t\t\t\t<texture file="makemake.jpg" />\n')
    elif i in [15, 16]:
        f.write('\t\t\t\t\t\t\t\t<texture file="ceres.jpg" />\n')
    elif i in [17, 18]:
        f.write('\t\t\t\t\t\t\t\t<texture file="eris.jpg" />\n')
    else:
        color(i)

def genY(x, z):
    y = random.randint(-10, 10)
    a = 1
    b = 2 * y
    c1 = pow(x, 2) + pow(y, 2) - pow(radius, 2)
    c2 = pow(z, 2) + pow(y, 2) - pow(radius, 2)
    d1 = pow(b, 2) - 4 * a * c1
    d2 = pow(b, 2) - 4 * a * c2
    y1 = (-b - math.sqrt(d1))/ (2 * a) + y
    y2 = (-b - math.sqrt(d2))/ (2 * a) + y
    return (y1, y2)

f.write('\t\t\t\t<group>\n')
for i in range(1, 28):
    f.write('\t\t\t\t\t<!-- #U' + str(i) + ' -->\n')
    f.write('\t\t\t\t\t<group>\n')
    f.write('\t\t\t\t\t\t<models>\n')
    f.write('\t\t\t\t\t\t\t<model file="sphere.3d"> <!-- generator sphere 1 20 20 sphere.3d -->\n')
    texture(i)
    f.write('\t\t\t\t\t\t\t</model>\n')
    f.write('\t\t\t\t\t\t</models>\n')
    f.write('\t\t\t\t\t\t<transform>\n')
    x = radius * math.sin(angle)
    z = radius * math.cos(angle)
    y = genY(x, z)
    time = random.randint(20, 50)
    args = buildTranslate(i, x, y, z)
    translate(i, time, args)
    scale(i)
    angle += inc
    f.write('\t\t\t\t\t\t</transform>\n')
    f.write('\t\t\t\t\t</group>\n\n')
f.write('\t\t\t\t</group>\n')

