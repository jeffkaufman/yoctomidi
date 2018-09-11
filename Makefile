yoctomidi: yoctomidi.m
	cd yoctolib/Examples/Doc-GettingStarted-Yocto-3D/ && make

clean:
	cd yoctolib/Examples/Doc-GettingStarted-Yocto-3D/ && make clean

run: yoctomidi
	./yoctomidi
