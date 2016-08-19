/*******************************************************************************
    Copyright (C) 2014-2016 Wright State University - All Rights Reserved
    Daniel P. Foose - Maintainer/Lead Developer

    This file is part of Vespucci.

    Vespucci is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Vespucci is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Vespucci.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#ifndef MULTIANALYZER_H
#define MULTIANALYZER_H
#include "Global/vespucciworkspace.h"
using namespace std;
using namespace arma;
///
/// \brief The MultiAnalyzer class
/// This class handles the execution of multivariate analysis across multiple
/// datasets. Each analysis method will create an AnalysisResults object smart
/// pointer that is shared by all datasets used, plus an auxiliary matrix in each
/// dataset for data that corresponds to spectra.
class MultiAnalyzer
{
public:
    MultiAnalyzer(QSharedPointer<VespucciWorkspace> workspace, QStringList dataset_keys);
    void Univariate(const QString &name,
                    double &left_bound,
                    double &right_bound,
                    uword bound_window);
    void BandRatio(const QString &name,
                   double &first_left_bound,
                   double &first_right_bound,
                   double &second_left_bound,
                   double &second_right_bound,
                   uword bound_window);
    void ClassicalLeastSquares(const QString &name,
                               const QString &reference_key);
    void VertexComponents(const QString &name,
                          uword endmembers);
    void KMeans(size_t clusters,
                const QString &metric_text,
                const QString &name);
    void PrincipalComponents(const QString &name);
    void PrincipalComponents(const QString &name,
                             bool scale_data);
    void PartialLeastSquares(const QString &name,
                             uword components);
    void AgglomerativeClustering(const QString &name,
                                 const QString &metric,
                                 const QString &linkage);
    bool CheckMergability(QStringList &keys, QStringList &problematic_keys);
    bool CheckMergability(const QStringList dataset_keys);
    bool ConcatenateMatrices(const QList<QStringList> &keys,
                             const sword &column);
    bool ConcatenateSpectra(QStringList dataset_keys);
private:
    QSharedPointer<VespucciWorkspace> workspace_;
    void GetDatasets(QStringList keys);
    void AddAnalysisResults(QSharedPointer<AnalysisResults> results, QStringList matrices);
    QString FindUniqueName(QString name);

    ///
    /// \brief data_
    /// stores the concatenated matrix
    mat data_;

    ///
    /// \brief abscissa_
    /// stores the abscissa common to all datasets
    vec abscissa_;
    ///
    /// \brief start_indices_
    /// Where each dataset begins
    uvec start_indices_;
    ///
    /// \brief end_indices_
    /// Where each dataset ends
    uvec end_indices_;

    ///
    /// \brief column_
    /// Which column to pull from source data
    sword column_;

    QVector<QSharedPointer<VespucciDataset> > datasets_;
};

#endif // MULTIANALYZER_H