import math, random

f = open("asteroides.xml", 'w')

angle = 0
inc = 2 * math.pi / 1000
radius = 155
random.seed(2)

def scale(i):
    if (i % 3) == 0:
        f.write('\t\t\t\t\t<scale x="0.10" y="0.10" z="0.10" />\n')
    elif (i % 3) == 1:
        f.write('\t\t\t\t\t<scale x="0.12" y="0.12" z="0.12" />\n')
    else:
        f.write('\t\t\t\t\t<scale x="0.15" y="0.15" z="0.15" />\n')


def buildTranslate():
    x = 165
    z = 235
    x_ = 115
    args = [0, 0, 0, 0, 0, 0, 0, 0]

    args[0] = f'\t\t\t\t\t<point x="{"{:.2f}".format(x)}" y="0" z="0"/>\n'
    args[1] = f'\t\t\t\t\t<point x="{"{:.2f}".format(x_)}" y="0" z="{"{:.2f}".format(-x)}"/>\n'    
    args[2] = f'\t\t\t\t\t<point x="0" y="0" z="{"{:.2f}".format(-z)}"/>\n'
    args[3] = f'\t\t\t\t\t<point x="{"{:.2f}".format(-x_)}" y="0" z="{"{:.2f}".format(-x)}"/>\n'
    args[4] = f'\t\t\t\t\t<point x="{"{:.2f}".format(-x)}" y="0" z="0"/>\n'
    args[5] = f'\t\t\t\t\t<point x="{"{:.2f}".format(-x_)}" y="0" z="{"{:.2f}".format(x)}"/>\n'
    args[6] = f'\t\t\t\t\t<point x="{"{:.2f}".format(0)}" y="0" z="{"{:.2f}".format(z)}"/>\n'
    args[7] = f'\t\t\t\t\t<point x="{"{:.2f}".format(x_)}" y="0" z="{"{:.2f}".format(x)}"/>\n'

    return args


def translate(i, time, args):
    i1 = i % 8
    i2 = (i1 + 1) % 8
    i3 = (i1 + 2) % 8
    i4 = (i1 + 3) % 8
    i5 = (i1 + 4) % 8
    i6 = (i1 + 5) % 8
    i7 = (i1 + 6) % 8
    i8 = (i1 + 7) % 8

    f.write(f'\t\t\t<transform>\n')
    f.write(f'\t\t\t\t<translate time = "{time}" align="False">\n')
    f.write(args[i1])
    f.write(args[i2])
    f.write(args[i3])
    f.write(args[i4])
    f.write(args[i5])
    f.write(args[i6])
    f.write(args[i7])
    f.write(args[i8])
    f.write('\t\t\t\t</translate>\n')
    f.write('\t\t\t</transform>\n')

def translateSingle(i, x, y, z):
    f.write(f'\t\t\t\t\t<translate x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y)}" z="{"{:.2f}".format(z)}"/>\n')

def color(i):
    f.write('\t\t\t\t\t\t<color>\n')
    f.write('\t\t\t\t\t\t<diffuse R="200" G="200" B="200" />')
    f.write('<ambient R="200" G="200" B="200" />')
    f.write('<specular R="250" G="250" B="250" />')
    f.write('<emissive R="0" G="0" B="0" />')
    f.write('<shininess value="127" />\n')
    f.write('\t\t\t\t\t\t</color>\n')

for j in range(1, 51):
    f.write('\t\t<group>\n')
    args = buildTranslate()
    time = random.randint(10, 25)
    translate(j, time, args)
    for i in range(1, 51):
        actualI = (j - 1) * 50 + i
        f.write('\t\t\t<!-- #A' + str(actualI) + ' -->\n')
        f.write('\t\t\t<group>\n')
        f.write('\t\t\t\t<models>\n')
        f.write('\t\t\t\t\t<model file="sphere.3d"> <!-- generator sphere 1 20 20 sphere.3d -->\n')
        color(i)
        f.write('\t\t\t\t\t</model>\n')
        f.write('\t\t\t\t</models>\n')
        f.write('\t\t\t\t<transform>\n')
        dist = random.randint(0, 20)
        x = random.randint(-15, 15)
        y = random.randint(-15, 15)
        z = random.randint(-15, 15)
        translateSingle(i, x, y, z)
        scale(i)
        f.write('\t\t\t\t</transform>\n')
        f.write('\t\t\t</group>\n\n')
    f.write('\t\t</group>\n')
    
f.close()
