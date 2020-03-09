#undef SEQAN_ENABLE_TESTING
#define SEQAN_ENABLE_TESTING 1

#include <seqan/seq_io.h>

#include <bifrost/ColoredCDBG.hpp>
#include <../src/ColoredDeBruijnGraph.h>

using namespace seqan;



template <typename TType>
inline void print(std::vector<TType> &v){
    std::cout << "[";
    // stay safe with constant iterators
    typename std::vector<TType>::const_iterator it = v.cbegin();
    for ( ; it != v.cend(); ++it){
        // output format
        std::cout << *it << ", ";
    }
    std::cout << "]" << std::endl;
}


/**
 * VERSION 2
 * This functions works. However it seems to work on 31 nucleotides even though I specified k=63
**/
inline void print_unitig_ends(ExtendedCCDBG &g){
    for (auto &ucm : g){

        DataAccessor<UnitigExtension>* da = ucm.getData();
        UnitigExtension* data = da->getData(ucm);

        size_t len = ucm.len;   // I assume this gets me the past-last-kmer index
        std::cout << data->getID() << " consists of " << len << "kmers." << std::endl;

        UnitigColorMap<UnitigExtension> k_first = ucm.getKmerMapping(0);    // seems to be 31 bp long, expected 63 bp
        UnitigColorMap<UnitigExtension> k_last  = ucm.getKmerMapping(len-1);    // seems to be 31 bp long, expected 63 bp

        const UnitigColors* k_first_colors = k_first.getData()->getUnitigColors(k_first);
        const UnitigColors* k_last_colors  =  k_last.getData()->getUnitigColors(k_last);

        std::vector<size_t> k_first_color_ids;
        std::vector<size_t> k_last_color_ids;

        // get color IDs of unitig's first kmer
        UnitigColors::const_iterator cit = k_first_colors->begin(k_first);
        for (; cit != k_first_colors->end(); ++cit){
            k_first_color_ids.push_back(cit.getColorID());
        }

        // get color IDs of unitig's last kmer
        cit = k_last_colors->begin(k_last);
        for (; cit != k_last_colors->end(); ++cit){
            k_last_color_ids.push_back(cit.getColorID());
        }

        // PRINT
        std::string first_seq = k_first.mappedSequenceToString();
        std::string last_seq  =  k_last.mappedSequenceToString();
        std::cout << data->getID() << " START COLORS (" << first_seq << "): " ; print(k_first_color_ids);
        std::cout << data->getID() << " END COLORS ("   << last_seq  << "): " ; print(k_last_color_ids);
    }
}


inline void init_ids_as_in_schematic(ExtendedCCDBG &xg){
    const char* u1_head = "CGTCAGCCGTCACCGAGCCTTATCTATGTCCCGACCAACAGAATAAACAGCAGCTACGCTTGA";
    Kmer u1_kmer = Kmer(u1_head);
    UnitigColorMap<UnitigExtension> u1 = xg.find(u1_kmer, true);
    DataAccessor<UnitigExtension>* da1 = u1.getData();
    UnitigExtension* data1 = da1->getData(u1);
    data1->setID(1u);

    const char* u2_head = "ATATATACATTTATAAATTTATATAAATATATATATTTATATATATATTTATCTTTATATTTG";
    Kmer u2_kmer = Kmer(u2_head);
    UnitigColorMap<UnitigExtension> u2 = xg.find(u2_kmer, true);
    DataAccessor<UnitigExtension>* da2 = u2.getData();
    UnitigExtension* data2 = da2->getData(u2);
    data2->setID(2u);

    const char* u3_head = "ACTCCGTGAATTGATCTGTTTGTCGAATACCCATGGTGTAAAGTGGAGGGTCCTACCCGCAAT";
    Kmer u3_kmer = Kmer(u3_head);
    UnitigColorMap<UnitigExtension> u3 = xg.find(u3_kmer, true);
    DataAccessor<UnitigExtension>* da3 = u3.getData();
    UnitigExtension* data3 = da3->getData(u3);
    data3->setID(3u);

    const char* u4_head = "ATATATACATTTATAAATTTATATAAATATATATATTTATATATATATTTATCTTTATATTTC";
    Kmer u4_kmer = Kmer(u4_head);
    UnitigColorMap<UnitigExtension> u4 = xg.find(u4_kmer, true);
    DataAccessor<UnitigExtension>* da4 = u4.getData();
    UnitigExtension* data4 = da4->getData(u4);
    data4->setID(4u);

    const char* u5_head = "TATATATACATTTATAAATTTATATAAATATATATATTTATATATATATTTATCTTTATATTT";
    Kmer u5_kmer = Kmer(u5_head);
    UnitigColorMap<UnitigExtension> u5 = xg.find(u5_kmer, true);
    DataAccessor<UnitigExtension>* da5 = u5.getData();
    UnitigExtension* data5 = da5->getData(u5);
    data5->setID(5u);
}


inline bool simple_lecc_unittest_truthset(/*TODO*/){

    std::string t1 = "ACTCCGTGAATTGATCTGTTTGTCGAATACCCATGGTGTAAAGTGGAGGGTCCTACCCGCAATAAAGTACCCTATCGCTAAATACCTATTGACGTGTTTTGACGGAATTTAAACTACAACGGCGGTGACATTAATGAGCTGAAGCCCGACCGCCCGCTGGGCGCGCCTCCTTGGGCAAGTTTTTTTTTTTTTTTTTTTTTGCTTTTAGGCCACATTCGGGTGGCGTCAACAGAAACGGTATATATACATTTATAAATTTATATAAATATATATATTTATATATATATTTATCTTTATATTTCCGGAGTTCAAATGAAAGATGCACAGCATTCACTCTATTTTTTTTTTTTTTTTTTTTTGCAACTGAATGCACCGATATAGTGCGTACCGCGTTGTATTCTTCTTGACAGTAAGTAATCCGTTCCATCGGTCAAGCTAGACCACTCGAACGTTTGAAGTGCTTTTGGTACCCTTTCACGGAGTTCACAAGATGGGCGCCTGGTTCGTTTGTGTTTGGGAAGGGCGGTGTCCATAGGCCA";

    std::string t2 = "CGTCAGCCGTCACCGAGCCTTATCTATGTCCCGACCAACAGAATAAACAGCAGCTACGCTTGAGGAAGCACAAGTAGCGTCCCAGTGGTTACTCCAATTACTGCCTGTATTGACTAAAGCAGCAGTGGTCGCCTCTACCCAAACAGGACATCCATAACTGTCTGAGCACTGGGTGTCACTGGGGGGGGGGGGGGGGGGGGTCACGACCAGAAACTAAGTAATAAAGGCGTTCGGCCTATATATATACATTTATAAATTTATATAAATATATATATTTATATATATATTTATCTTTATATTTGCACACCTTCCTTCGGAACGACCGTCAGATTCACCTGCGGGGGGGGGGGGGGGGGGGGAAGGAAGCCGAGAACTCAAACCCACGCACCCTATGAGTAGTCCTACACGTCCATCGAGACCTCTCGTACTTGATGACACACACCCATATGCCAAATTCTTATCTGTACCTCTTATTCAAGAAGCGTGGCCCGACCTCACATCATATACACTGAGCATGGTGGTCGATATTACAGAACATG";

}



// -----------------
// | LECC UNITTEST |
// -----------------
CCDBG_Build_opt opt_lecc_unittest;

SEQAN_DEFINE_TEST(setup_simple_lecc_unittest){

    std::vector<std::string> i_files;

    i_files.push_back("./data/lecc_unittest/sample1.fa");
    i_files.push_back("./data/lecc_unittest/sample2.fa");
    i_files.push_back("./data/lecc_unittest/sample3.fa");
    i_files.push_back("./data/lecc_unittest/sample4.fa");

    opt_lecc_unittest.filename_ref_in = i_files;
    opt_lecc_unittest.deleteIsolated = true;
    opt_lecc_unittest.clipTips = true;
    opt_lecc_unittest.prefixFilenameOut = "lecc_unittest";
    opt_lecc_unittest.nb_threads = 1;
    opt_lecc_unittest.outputGFA = true;
    opt_lecc_unittest.verbose = false;
    opt_lecc_unittest.k = 63;
}


// -----------------
// | CCDBG UNITTEST |
// -----------------
SEQAN_DEFINE_TEST(simple_lecc_unittest){

    ExtendedCCDBG xg(opt_lecc_unittest.k, opt_lecc_unittest.g);

    /* DEBUG */ std::cout << "MAX_KMER_SIZE=" << MAX_KMER_SIZE << std::endl;
    /* DEBUG */ std::cout << "ExtendedCCDBG::getK()=" << xg.getK() << std::endl;

    SEQAN_ASSERT_EQ(xg.buildGraph(opt_lecc_unittest),true);

    SEQAN_ASSERT_EQ(xg.simplify(opt_lecc_unittest.deleteIsolated, opt_lecc_unittest.clipTips, opt_lecc_unittest.verbose),true);

    SEQAN_ASSERT_EQ(xg.buildColors(opt_lecc_unittest),true);

    xg.init_ids();

    init_ids_as_in_schematic(xg);

    /* DEBUG */ print_unitig_ends(xg);

    xg.traverse();

    SEQAN_ASSERT_EQ(xg.write(opt_lecc_unittest.prefixFilenameOut, opt_lecc_unittest.nb_threads, opt_lecc_unittest.verbose), true);
}


SEQAN_BEGIN_TESTSUITE(test_popins2){

    SEQAN_CALL_TEST(setup_simple_lecc_unittest);

    SEQAN_CALL_TEST(simple_lecc_unittest);
}
SEQAN_END_TESTSUITE
