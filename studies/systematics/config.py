import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/../..")
from config_base import *

#--------------------

for c in all_cfg:
  c.anal.use_resolution_fits = False

#--------------------

cfg_45b_56t.anal.L_int = 1

#--------------------

cfg_45t_56b.anal.L_int = 1
