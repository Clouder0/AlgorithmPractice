from dataclasses import dataclass


@dataclass
class candidate:
    rk: int
    info: str
    duplicate: bool


C = [
    [
        candidate(1, "马文训 220330103", False),
        candidate(2, "朱伟文 2023312A14", True),
    ],
    [
        candidate(3, "赵庭葳 220720122", False),
        candidate(4, "张浩炜 2023312420", True),
        candidate(5, "邹乐添 210110701", True),
        candidate(6, "熊广源 2023313608", False),
        candidate(7, "张家霖 22s15081", True),
        candidate(8, "张天宇 190320313", False),
    ],
    [
        candidate(9, "梁泽宇 2023312422", True),
        candidate(10, "姚瀚舒 2023311705", False),
        candidate(11, "李梓维 2023312631", False),
        candidate(12, "祝一帆 2023311C07", False),
        candidate(13, "裴俊博 210810207", True),
        candidate(14, "余洪波 23S153111", False),
        candidate(15, "李春江 2023317105", False),
        candidate(16, "杨雨彤 2023314331", True),
    ],
    [
        candidate(17, "申孟忻 210330114", False),
        candidate(18, "陈虹旭 2023315205", False),
    ],
    [],
]

P1 = []
P2 = []
P3 = []
nowC = 0


def arrange(P: list, num: int):
    global nowC
    while len(P) < num:
        if len(C[nowC]) == 0:
            nowC += 1
            if nowC >= 4:
                print("Error!")
                exit()
            continue
        if C[nowC][0].duplicate:
            nc = C[nowC].pop(0)
            nc.duplicate = False
            C[nowC + 1].append(nc)
            continue
        P.append(C[nowC].pop(0))


arrange(P1, 2)
arrange(P2, 6)
arrange(P3, 8)

print("一等奖")
for x in P1:
    print(x.rk, x.info)
print("二等奖")
for x in P2:
    print(x.rk, x.info)
print("三等奖")
for x in P3:
    print(x.rk, x.info)
