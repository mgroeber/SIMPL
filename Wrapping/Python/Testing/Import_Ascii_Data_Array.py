# Pipeline: Import Ascii Data Array Test

import simpl
import simplpy
import simpl_helpers as sh
import simpl_test_dirs as sd

def import_ascii_array_test():
    # Create Data Container Array using simpl directly
    dca = simpl.DataContainerArray()

    # Create a Data Container using the pythonic version
    err = simplpy.create_data_container(dca, 'DataContainer')
    assert err == 0

    # Create an Attribute Matrix
    amDims = [[143, 1, 1]]
    tableData = sh.CreateDynamicTableData(amDims)
    dap = simpl.DataArrayPath('DataContainer', 'CellAttributeMatrix', '')
    err = simplpy.create_attribute_matrix(dca, dap, simpl.AttributeMatrix.Type.Cell, tableData)
    assert err == 0

    # Import ASCII Data Attribute Array
    err = simplpy.import_asci_data_array(dca, simpl.DataArrayPath('DataContainer', 'CellAttributeMatrix', 'AsciiData'),
                                         simpl.NumericTypes.Float, 3, 1,
                                         sd.GetBuildDirectory() + '/Data/SIMPL/VertexCoordinates.csv',
                                         simpl.DelimiterTypes.Comma)
    assert err == 0, f'ImportAsciiDataArray ErrorCondition: {err}'

    # Export ASCII Data
    # Output Style = 0 Means Multiple Files, Style = 1 Means a Single file
    outStyle = 0 
    selected_data_array_paths = [simpl.DataArrayPath('DataContainer', 'CellAttributeMatrix', 'AsciiData')]
    err = simplpy.write_ascii_data(dca, selected_data_array_paths,
                                   sd.GetBuildDirectory() + '/Data/Output/CoreFilters', # Only needed for Multi-File output
                                   sd.GetBuildDirectory() + '/Data/Output/CoreFilters/AcsiiOutput.csv', # Only needed for Single File Style
                                   simpl.DelimiterTypes.Comma, '.csv', 10, outStyle)
    assert err == 0, f'WriteAsciiData ErrorCondition: {err}'

if __name__ == '__main__':
    import_ascii_array_test()
