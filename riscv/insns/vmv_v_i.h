// vmv.v.i vd, simm5
require_vector;
VI_CHECK_SSS(false);
VI_VVXI_MERGE_LOOP
({
  vd = simm5;
})
