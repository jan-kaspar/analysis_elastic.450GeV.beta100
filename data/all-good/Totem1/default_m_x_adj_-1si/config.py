import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
    c.anal.si_th_x_2arm = si_th_x_1arm / math.sqrt(2.) - 2.5E-6

#----------

