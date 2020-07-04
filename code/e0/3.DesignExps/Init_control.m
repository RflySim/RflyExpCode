path(path, './icon/');

%模型参数 运行模型初始化文件icon/init.m
Init;


kFactor = 1.2;

KpRollAttitude = 0.630138625117681 / kFactor;
KiRollAttitude = 0.0552303199591522 / kFactor;

KpPitchAttitude = 0.630138625117681 / kFactor;
KiPitchAttitude = 0.0552303199591522 / kFactor;

KpRollRate = 1.31533836563383 / kFactor;
KiRollRate = 0.460338699849681 / kFactor;

KpPitchRate = 1.31533836563383 / kFactor;
KiPitchRate = 0.460338699849681 / kFactor;

KpYawRate = 1.31533836563383 / kFactor * 2;
KiYawRate = 0.460338699849681 / kFactor * 2;


