# core
#HFLEDAnalyzer.C for analysing data taken for LED of the CMS HCAL HF PMT Gains 
#HFSPEAnalyzer.C for analysing data taken for SPE of the CMS HCAL HF PMT Gains


#Analysises in Analyzers for LEDs and SPEs runs

 a - Channels vs GAIN for DB0 and DB1 at 650V
 b - Channels vs GAIN for DB0 and DB1 at 700V
 c - GAIN vs HVs 
 d - Gain Correlation vs HVs
 e - Gain Correlation for DBs (Reds are DB0, Blue ones are DB1)
 f - Gains Correlation at HVs in different DBs  (Reds are 650V for DB0 and DB1, Blue ones are 700V for DB0 and DB1)
 g - TTreeofGAINs
 h - NtuplesofGAINs
 j - NtuplesofGAINsfor650V
 k - NtuplesofGAINsfor700V
 l - TTreeofGAINsforHVs
 m - NtuplesofGAINsforHVs
 n - GAINforHVsandDBs
 p - Gain Correlation in different DBs at 650V
 r - Gain Correlation in different DBs at 700V
 s - Gain Correlation in differetn HVs at DB1
 t - Gain Correlation in differetn HVs at DB0
 v - All of the Analyse above for Quadrants 
 y - All of the Analyse above for HFM 
 x - All of the	Analyse	above for HFP
 z - Gain Correlation for all runs
 o - Gain Correlation for Quadrants
 i - Gain Correlation for HFM 
 u - Gain Correlation for HFP 


#LED QUADRANTs
HFP_Q1 — 2999-3002-3005-3010-3013
HFP_Q2 — 3016-3019-3025-3028-3031
HFP_Q3 — 3034-3036-3039-3042-3045
HFP_Q4 — 2983-2987-2990-2993-2996

HFM_Q1 — 3048-3054-3057-3060-3063(DB0)
HFM_Q2 —3063(DB1)-3066-3069-3072-3076
HFM_Q3 —3079-3082-3085-3088-3091(DB0)
HFM_Q4 — 3091(DB1)-3095-3098-3101-3104

#SPE QUADRANTs
HFP_Q1 — 2998-3001-3004-3009-3012
HFP_Q2 — 3015-3018-3024-3027-3030
HFP_Q3 — 3033-3037-3040-3043-3046
HFP_Q4 —2982-2986-2989-2992-2995

HFM_Q1 —3049-3055-3058-3061-3064(DB0)
HFM_Q2 —3064(DB1)-3067-3070-3073-3077
HFM_Q3 —3080-3083-3086-3089-3092(DB0)
HFM_Q4 — 3092(DB1)-3096-3099-3102-3105


#LED HFP QUADRANTs
HFP-2999-3002-3005-3010-3013-3016-3019-3025-3028-3031-3034-3036-3039-3042-3045-2983-2987-2990-2993-2996
#LED HFM QUADRANTs
3048-3054-3057-3060-3063(DB0)-3063(DB1)-3066-3069-3072-3076-3079-3082-3085-3088-3091(DB0)-3091(DB1)-3095-3098-3101-3104
#SPE HFP QUADRANTs
2998-3001-3004-3009-3012-3015-3018-3024-3027-3030-3033-3037-3040-3043-3046-2982-2986-2989-2992-2995 
#SPE HFM QUADRANTs
3049-3055-3058-3061-3064(DB0)-3064(DB1)-3067-3070-3073-3077-3080-3083-3086-3089-3092(DB0)-3092(DB1)-3096-3099-3102-3105


#Runs filled only DB0 of 
LED - 3013,3031,3045,2996 
SPE - 3012,3030,3046,2995 

#Read and Write *csv file
Firstly, Convert *.xlsx file to *.csv file as comma-sperated values on Excel ,and then use the command "sed -i -e 's/,/./g;s/;/,/g' filename.csv" on terminal,
Finally, run the script readfromCSV.C, 
At first aspect, all data will be found on HamamatsuInfo.txt as string, convert string to double on into the script, and all process as desired, such as GAIN calculations,
will be able to be ready to do ...       

#Baseboards.C
read data from Baseboard&d.txt ,and then write them in AllPMTIDs.txt and in BaseboardVsPMTIDs.txt 
