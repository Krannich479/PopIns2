#include <iostream>

#include "argument_parsing.h"           /* seqAn argument parser */
#include "popins2_single_sample_dBG.h"

#include "ColoredCDBG_Data_extension.h"
#include "ColoredCDBG_Graph_extension.h"

#include "../../prettyprint/prettyprint.h"      // my debug headder

using namespace std;



// ==============================
// Function: main()
// ==============================
int main(int argc, char const *argv[]){

    /*
    // ==============================
    // Argument Parser
    // ==============================
    OptionsWrapper options;
    seqan::ArgumentParser::ParseResult res = parseCommandLine(options, argc, argv);
    // catch parse error
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res == seqan::ArgumentParser::PARSE_ERROR;

    // ==============================
    // Read FastX files
    // ==============================
    vector<string> sample_fastx_names;      // all file names in --indir with full path
    bool isFilereadSuccessful = detect_indir_files(options, sample_fastx_names);

    // ==============================
    // Initialize graph
    // ==============================
    CCDBG_Build_opt graph_options;
    if(isFilereadSuccessful==EXIT_SUCCESS)
        init_graph_options(options, sample_fastx_names, graph_options);
    if(!check_ProgramOptions(graph_options))
        return 1;   // some input options are not appropriate to construct the CDBG

    // ==============================
    // Run graph functions
    // ==============================
    ExtendedCCDBG ccdbg(graph_options.k, graph_options.g);
    cout << "[PROGRESS] Building CCDBG..." << endl;
    ccdbg.build(graph_options);

    // simplify
    cout << "[PROGRESS] Simplifying CCDBG..." << endl;
    ccdbg.simplify(graph_options.deleteIsolated, graph_options.clipTips, graph_options.verbose);

    // write
    cout << "[PROGRESS] Writing GFA..." << endl;
    ccdbg.write(graph_options.prefixFilenameOut, graph_options.nb_threads, graph_options.verbose);
    cout << "[DEBUG] The DBG has " << ccdbg.size() << " unitigs.\n" << endl;
    */

    // TEST START
    popins_single_sample_dBG(argc, argv);

    /*
    ccdbg.init_ids();
    ccdbg.connected_components(graph_options);
    */

    // WARNING: add a bool whether dfs/bfs (=xfs) variables are on initial state
    /*
    for (auto &unitig : cdbg)
        if (unitig.getData()->getID() == 3)    // test case: unitig ID 3 as source
            cdbg.dfs(unitig);
    */

    //cdbg.print_unitig_info();

    /*
    ccdbg.init_kmer_cov();
    ccdbg.annotate_kmer_coverage(sample_fastx_names);
    */

    /*
    for ( auto &unitig : ccdbg){
        DataAccessor<UnitigExtension>* da = unitig.getData();
        UnitigExtension* ue = da->getData(unitig);

        cout << "[[" << ue->getID() << "]]";
        prettyprint::print(ue->kmer_coverage);
        cout << endl;
    }
    */

    // ccdbg.small_bubble_removal();

    // TEST END


    return 0;
}



