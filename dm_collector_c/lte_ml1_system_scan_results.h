/*
 * LTE ML1 System Scan Results
 */

#include "consts.h"
#include "log_packet.h"
#include "log_packet_helper.h"

const Fmt LteMl1SystemScanResults_Fmt [] = {
    {UINT, "Version", 1},
};

const Fmt LteMl1SystemScanResults_Payload_v2 [] = {
    {SKIP, NULL, 1},
    {UINT, "Num Candidates", 2}
};

const Fmt LteMl1SystemScanResults_Candidate_v2 [] = {
    {UINT, "EARFCN", 4},
    {UINT, "Band", 2},
    {UINT, "Bandwidth (MHz)", 2},   // (x-1)*5
    {UINT, "Energy (dBm/100KHz)", 2},   // x-65536
    {SKIP, NULL, 2},
};


static int _decode_lte_ml1_system_scan_results_payload (const char *b,
        int offset, size_t length, PyObject *result) {
    int start = offset;
    int pkt_ver = _search_result_int(result, "Version");

    switch (pkt_ver) {
    case 2:
        {
            offset += _decode_by_fmt(LteMl1SystemScanResults_Payload_v2,
                    ARRAY_SIZE(LteMl1SystemScanResults_Payload_v2, Fmt),
                    b, offset, length, result);
            int num_candidate = _search_result_int(result, "Num Candidates");

            PyObject *result_record = PyList_New(0);
            for (int i = 0; i < num_candidate; i++) {
                PyObject *result_record_item = PyList_New(0);
                offset += _decode_by_fmt(LteMl1SystemScanResults_Candidate_v2,
                        ARRAY_SIZE(LteMl1SystemScanResults_Candidate_v2, Fmt),
                        b, offset, length, result_record_item);
                int iBandwidth = _search_result_int(result_record_item,
                        "Bandwidth (MHz)");
                iBandwidth = (iBandwidth - 1) * 5;
                PyObject *old_object = _replace_result_int(result_record_item,
                        "Bandwidth (MHz)", iBandwidth);
                Py_DECREF(old_object);
                int iEnergy = _search_result_int(result_record_item,
                        "Energy (dBm/100KHz)");
                iEnergy -= 65536;
                old_object = _replace_result_int(result_record_item,
                        "Energy (dBm/100KHz)", iEnergy);
                Py_DECREF(old_object);

                PyObject *t1 = Py_BuildValue("(sOs)", "Ignored",
                        result_record_item, "dict");
                PyList_Append(result_record, t1);
                Py_DECREF(t1);
                Py_DECREF(result_record_item);
            }
            PyObject *t = Py_BuildValue("(sOs)", "Candidates",
                    result_record, "list");
            PyList_Append(result, t);
            Py_DECREF(t);
            Py_DECREF(result_record);
            return offset - start;
        }
    default:
        printf("Unknown LTE PDSCH Stat Indication version: 0x%x\n", pkt_ver);
        return 0;
    }
}