/* SymResponse: a unified framework for response theory
   Copyright 2024 Bin Gao

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   This file is the header file of Lagrangian in atomic-orbital density matrix
   based response theory.

   2024-01-30, Bin Gao:
   * first version
*/

#pragma once

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symengine_rcp.h>

#include <Tinned.hpp>

#include "SymResponse/Lagrangian.hpp"

namespace SymResponse
{
    /* Time-averaged quasi-energy derivative Lagrangian */
    class LagrangianDAO: virtual public Lagrangian
    {
        protected:
            // Whether elimination rules performed in a (almost) symmetric form
            // or not [see Sec. IV G 3, J. Chem. Phys. 129, 214108 (2008)]
            bool sym_elimination_;
            // Perturbation $a$
            SymEngine::RCP<const Tinned::Perturbation> a_;
            // One-electron spin-orbital density matrix
            SymEngine::RCP<const Tinned::OneElecDensity> D_;
            // Overlap
            SymEngine::RCP<const Tinned::OneElecOperator> S_;

            // Generalized energy
            SymEngine::RCP<const SymEngine::Basic> E_;
            // Generalized Fock matrix, the sum of one-electron operator(s),
            // two-electron operator(s) and exchange-correlation potential(s)
            SymEngine::RCP<const SymEngine::Basic> F_;
            // Generalized energy-weighted density matrix
            SymEngine::RCP<const SymEngine::Basic> W_;
            // Lagrangian multiplier $\lambda$
            SymEngine::RCP<const SymEngine::Basic> lambda_;
            // TDSCF equation
            SymEngine::RCP<const SymEngine::Basic> Y_;
            // Lagrangian multiplier $\zeta$
            SymEngine::RCP<const SymEngine::Basic> zeta_;
            // Idempotency constraint
            SymEngine::RCP<const SymEngine::Basic> Z_;

        public:
            explicit LagrangianDAO(
                const SymEngine::RCP<const Tinned::Perturbation>& a,
                const SymEngine::RCP<const Tinned::OneElecDensity>& D,
                const SymEngine::RCP<const SymEngine::Basic>& S = SymEngine::RCP<const SymEngine::Basic>(),
                const SymEngine::vec_basic& H = {},
                const SymEngine::RCP<const SymEngine::Basic>& G = SymEngine::RCP<const SymEngine::Basic>(),
                const SymEngine::RCP<const SymEngine::Basic>& Exc = SymEngine::RCP<const SymEngine::Basic>(),
                const SymEngine::RCP<const SymEngine::Basic>& Fxc = SymEngine::RCP<const SymEngine::Basic>(),
                const SymEngine::RCP<const SymEngine::Basic>& hnuc = SymEngine::RCP<const SymEngine::Basic>(),
                const bool sym_elimination = false
            );

            virtual SymEngine::RCP<const SymEngine::Basic> get_response_functions(
                // Extensive perturbations without `a`
                const Tinned::PerturbationTuple& exten_perturbations,
                const Tinned::PerturbationTuple& inten_perturbations = {},
                const unsigned int min_wfn_extern = 0
            ) override;

            //virtual SymEngine::RCP<const SymEngine::Basic> get_residues(
            //    // Extensive perturbations without `a`
            //    const Tinned::PerturbationTuple& exten_perturbations,
            //    const Tinned::PerturbationTuple& inten_perturbations = {},
            //    const unsigned int min_wfn_extern = 0
            //) override;

            // Set elimination rules performed either in an asymmetric
            // (`false`) or (almost) symmetric (`true`) form
            inline void set_elimination_form(const bool sym_elimination) noexcept
            {
                sym_elimination_ = sym_elimination;
            }

            // Whether elimination rules performed in an asymmetric (`false`)
            // or (almost) symmetric (`true`) form
            inline bool get_elimination_form() const noexcept
            {
                return sym_elimination_;
            }

            // Get perturbation $a$
            inline SymEngine::RCP<const Tinned::Perturbation> get_perturbation_a() const noexcept
            {
                return a_;
            }

            // Get one-electron spin-orbital density matrix
            inline SymEngine::RCP<const Tinned::OneElecDensity> get_density() const noexcept
            {
                return D_;
            }

            // Get overlap matrix
            inline SymEngine::RCP<const Tinned::OneElecOperator> get_overlap() const noexcept
            {
                return S_;
            }

            // Get generalized energy
            inline SymEngine::RCP<const SymEngine::Basic> get_generalized_energy() const noexcept
            {
                return E_;
            }

            // Get generalized Fock matrix
            inline SymEngine::RCP<const SymEngine::Basic> get_generalized_fock() const noexcept
            {
                return F_;
            }

            // Get generalized energy-weighted density matrix
            inline SymEngine::RCP<const SymEngine::Basic> get_ew_density() const noexcept
            {
                return W_;
            }

            // Get Lagrangian multiplier $\lambda$
            inline SymEngine::RCP<const SymEngine::Basic> get_tdscf_multiplier() const noexcept
            {
                return lambda_;
            }

            // Get TDSCF equation
            inline SymEngine::RCP<const SymEngine::Basic> get_tdscf_equation() const noexcept
            {
                return Y_;
            }

            // Get Lagrangian multiplier $\zeta$
            inline SymEngine::RCP<const SymEngine::Basic> get_idempotency_multiplier() const noexcept
            {
                return zeta_;
            }

            // Get idempotency constraint
            inline SymEngine::RCP<const SymEngine::Basic> get_idempotency_constraint() const noexcept
            {
                return Z_;
            }

            virtual ~LagrangianDAO() noexcept = default;
    };
}